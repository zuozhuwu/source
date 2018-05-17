#include "stdafx.h"
#include <math.h>

CValveSystem::CValveSystem()
{
	m_maxVelocity = 150;
	m_Time = 2e6;
}

void CValveSystem::connect(CMyObject& obj1, portType port1, CMyObject& obj2, portType port2)   //connect one port of object1 to anther port of object2
{
	objPortPair part1;
	part1.obj = &obj1;
	part1.port = port1;

	objPortPair part2;
	part2.obj = &obj2;
	part2.port = port2;

	m_connectors.push_back(part1);      //pairs like (0, 1) (2, 3) (4, 5)
	m_connectors.push_back(part2);

	addToTankList(&obj1);
	addToValveList(&obj1);
	addToTankList(&obj2);
	addToValveList(&obj2);
}

void CValveSystem::solve(int timeStep)
{
	m_timeStep = timeStep;	

	vector<vector<objPortPair>> vecLines;

	for (size_t i = 0; i < m_vecTanks.size(); i++)    //for all tanks
	{		
		vector<objPortPair> vecConnectingToTank = findConnectorToTank(m_vecTanks[i]);   //find all the things connected to the tanks

		for (size_t j = 0; j < vecConnectingToTank.size(); j++)
		{

			vector<objPortPair> oneLine;

			objPortPair tank;
			tank.obj = (CMyObject*)m_vecTanks[i];
			tank.port = CValve::valvePort::intake;

			oneLine.push_back(tank);
			oneLine.push_back(vecConnectingToTank[j]);

			handleValve();    //extract all the internal connections in valve

			bool keepFinding = true;

			int findTimes = 0;

			objPortPair * target = &(vecConnectingToTank[j]);

			objPortPair* found = new objPortPair;

			while (keepFinding)
			{
				if (findTimes % 2 == 0)
				{
					keepFinding = findInComp(*target, *found);

					if (keepFinding)
					{
						oneLine.push_back(*found);
						target = found;
					}
				}
				else
				{
					*found = findBetweenComp(*target);
					oneLine.push_back(*found);
					target = found;
				}

				findTimes++;
			}

			delete found;

			if (!isLineExist(vecLines, oneLine))    //line not exist in vecLines
			{
				vecLines.push_back(oneLine);

				handleOneLine(oneLine);
			}		
		}		
	}   //we get all lines
}

void CValveSystem::handleOneLine(vector<objPortPair> & line)    
{
	if (line.size() < 2)
	{
		showMsg("only one object, nothing to calculate!");

		return;
	}

	objPortPair first = line[0];

	objPortPair last = line[line.size() - 1];

	if (first.obj->getTypeName() == "CTank" && last.obj->getTypeName() == "CTank")   //the beginning and the end of the line is tank
	{    //calulate the mass flow
		if (line.size() < 3)
		{
			showMsg("can not connect a tank to another tank directly");

			return;
		}
		else   //get at lease 3 components
		{
			objPortPair middle = line[1];

			calcFlowRate((CTank*)first.obj, (CValve*)middle.obj, (CTank*)last.obj);

		}
	}

	setComponetPres(line);

}

void CValveSystem::calcFlowRate(CTank* tank1, CValve* valve, CTank* tank2)
{
	double pres1 = tank1->getPortPres();
	double pres2 = tank2->getPortPres();

	double deltP = fabs(pres1 - pres2);

	double velocity = m_maxVelocity * (1 - exp(-1 * deltP / m_Time));
	
	ubyte connectCode = valve->getPosCode();

	double area1 = valve->m_portArea[connectCode >> 4];
	double area2 = valve->m_portArea[connectCode & 0x0F];

	double area = (area1 + area2) / 2;

	//double coeff = valve->getFlowRateCoeff();

	//double massFlowRate = coeff * area * (pres1 - pres2);           //the mass flow rate is calculated by 0.0135 * deltP * S, refer to my IFAC paper	

	double massFlowRate = area * velocity * 1.29;

	if (pres1 > pres2)
	{
		tank1->changePresByFlow(massFlowRate, m_timeStep);

		tank2->changePresByFlow(-1 * massFlowRate, m_timeStep);
	}
	else
	{
		tank1->changePresByFlow(-1 * massFlowRate, m_timeStep);

		tank2->changePresByFlow(massFlowRate, m_timeStep);
	}

	
}


void CValveSystem::addToTankList(CMyObject* obj)
{
	if (obj->getTypeName() != "CTank") return;      //it is not a Tank, return

	bool found = false;        

	for (size_t i = 0; i < m_vecTanks.size(); i++)
	{
		if (obj->getObjIndex() == m_vecTanks[i]->getObjIndex())
		{
			found = true;              //already in m_valves
			break;
		}
	}

	if (!found)
	{
		m_vecTanks.push_back((CTank*)obj);
	}
}

void CValveSystem::addToValveList(CMyObject* obj)
{
	if (obj->getTypeName() != "CValve") return;      //it is not a valve, return

	bool found = false;

	for (size_t i = 0; i < m_vecValves.size(); i++)
	{
		if (obj->getObjIndex() == m_vecValves[i]->getObjIndex())
		{
			found = true;              //already in m_valves
			break;
		}
	}

	if (!found)
	{
		m_vecValves.push_back((CValve*)obj);
	}
}

void CValveSystem::setComponetPres(vector<objPortPair> line)
{
	CTank* tank0 = (CTank*)line[0].obj;

	double pres0 = tank0->getPortPres();

	if (line[line.size() - 1].obj->getTypeName() != "CTank")   //the last one is not a tank
	{
		
		for (int i = 1; i < (int)line.size(); ++i)
		{
			CValve* v = (CValve*)line[i].obj;
			v->setPortPres(pres0, line[i].port);
		}
	}
	else     //the last one is a tank
	{
		CTank* tank1 = (CTank*)line[line.size() - 1].obj;
		double pres1 = tank1->getPortPres();

		CValve* v = (CValve*)line[1].obj;
		v->setPortPres(pres0, line[1].port);

		for (int i = 2; i < (int)line.size() - 1; ++i)
		{
			CValve* v = (CValve*)line[i].obj;
			v->setPortPres(pres1, line[i].port);
		}
	}
}

objPortPair CValveSystem::findBetweenComp(objPortPair onePort)
{
	size_t i = 0;

	for (; i < m_connectors.size(); i++)
	{
		objPortPair anotherPort = m_connectors[i];

		if (onePort.obj->getObjIndex() == anotherPort.obj->getObjIndex() &&
			onePort.port == anotherPort.port)
		{
			break;
		}
	}

	if (i % 2 == 0)                              // (0 1)  (2 3)   (4 5)   pairs like this
	{
		if (i + 1 >= m_connectors.size())
		{
			char str[128];
			sprintf_s(str, "missing connection to object (%s) with index %d  in port %d", onePort.obj->getTypeName(), onePort.obj->getObjIndex(), onePort.port);			

			showMsg(str);
			exit(-1);
		}

		return m_connectors[i + 1];
	}
	else
	{
		return m_connectors[i - 1];
	}

}

bool CValveSystem::findInComp(const objPortPair& onePort, objPortPair& result)
{
	size_t i = 0;

	for (; i < m_valveConnectors.size(); i++)
	{
		objPortPair anotherPort = m_valveConnectors[i];

		if (onePort.obj->getObjIndex() == anotherPort.obj->getObjIndex() &&
			onePort.port == anotherPort.port)
		{
			break;
		}
	}

	if (i == m_valveConnectors.size())
	{
		return false;
	}
	else
	{
		if (i % 2 == 0)                              // (0 1)  (2 3)   (4 5)   pairs like this
		{
			result = m_valveConnectors[i + 1];
		}
		else
		{
			result =  m_valveConnectors[i - 1];
		}

		return true;
	}
}

portType CValveSystem::getPortTypeByInt(ubyte i)
{
	if (0 == i)
	{
		return CValve::valvePort::controlPort;
	}
	else if (1 == i)
	{
		return CValve::valvePort::intake;
	}
	else if (2 == i)
	{
		return CValve::valvePort::outtake;
	}
	else if (3 == i)
	{
		return CValve::valvePort::exhaust;
	}
	else
	{	
		return CValve::valvePort::controlPort;
	}
}


vector<objPortPair> CValveSystem::findConnectorToTank(CTank* tank)
{
	vector<objPortPair> retVector;

	for (size_t i = 0; i < m_connectors.size(); i++)
	{
		if (m_connectors[i].obj->getObjIndex() == tank->getObjIndex() && m_connectors[i].port == CValve::valvePort::intake)   //find the tank
		{
			if (i % 2 == 0)
			{
				retVector.push_back(m_connectors[i + 1]);
			}
			else
			{
				retVector.push_back(m_connectors[i - 1]);
			}
		}
	}	

	return retVector;
}

void CValveSystem::handleValve()
{
	m_valveConnectors.clear();

	for (size_t i = 0; i < m_vecValves.size(); i++)
	{
		CValve* v = m_vecValves[i];

		v->valveCtrl();  

		ubyte code = v->getPosCode();

		if (code == 0) continue;

		objPortPair p1;
		p1.obj = v;
		p1.port = getPortTypeByInt(code & 0x0F);

		objPortPair p2;
		p2.obj = v;
		p2.port = getPortTypeByInt(code >> 4);

		m_valveConnectors.push_back(p1);

		m_valveConnectors.push_back(p2);
	}
}

bool CValveSystem::isLineExist(vector<vector<objPortPair>> & lines, vector<objPortPair> & line)
{
	bool ret = false;

	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<objPortPair> target = lines[i];

		if (target.size() != line.size())    //the size of two vectors is not same
		{
			continue;
		}
		else    //has the same size
		{
			bool same = true;
			for (size_t j = 0; j < target.size(); j++)
			{
				if (target[j].obj->getObjIndex() != line[j].obj->getObjIndex()  &&                      //from one end
					target[j].obj->getObjIndex() != line[target.size() - j -1].obj->getObjIndex())       //from another end
				{
					same = false;
					break;
				}
			}

			if (same)    //find the same line
			{
				ret = true;
				break;
			}
			else
			{
				continue;   //keep finding
			}
		}
	}
	return ret;
}

void CValveSystem::showMsg(string msg)
{
#ifdef _CONSOLE       //make sure it is console program
	cout << msg << endl;
#endif
}

void CValveSystem::saveData(int time)
{
	for (size_t i = 0; i < objList.size(); i++)
	{
		CMyObject* obj = objList[i];
		obj->saveData(time);
	}
}