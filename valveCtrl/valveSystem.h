#pragma once
#include "stdafx.h"
#include <vector>

struct objPortPair        //object and port pair
{
	CMyObject* obj;
	portType port;
};

//this class is used to connect all the valves and tanks.
class CValveSystem
{
private:
	vector<CValve*> m_vecValves;
	vector<CTank*> m_vecTanks;
	vector<objPortPair> m_connectors;
	vector<objPortPair> m_valveConnectors;
	int m_timeStep;

	double m_maxVelocity;   //the max gas flow velocity
	double m_Time;          //the period, time constant

public:
	CValveSystem();
	~CValveSystem(){};

	void connect(CMyObject& obj1, portType port1, CMyObject& obj2, portType port2);   //connect one port of object1 to anther port of object2

	void solve(int timeStep);      //timestep:ms

	void saveData(int time);

private:
	void addToTankList(CMyObject* obj);   //add tanks to m_vecTanks, make sure no reduplicate

	void addToValveList(CMyObject* obj);

	objPortPair findBetweenComp(objPortPair onePort);   //find connected pair

	bool findInComp(const objPortPair& find, objPortPair& result);

	portType getPortTypeByInt(ubyte i);    //convert int 1 to portType intakePort
	
	vector<objPortPair> findConnectorToTank(CTank* tank);    // find all things that connecting to a tank	

	void handleValve();      //retrieve all the internal connection in a valve	

	bool isLineExist(vector<vector<objPortPair>> & lines, vector<objPortPair> & line);    //is line exist in lines

	void handleOneLine(vector<objPortPair> & line);

	void calcFlowRate(CTank* tank1, CValve* valve, CTank* tank2);

	void setComponetPres(vector<objPortPair> line);

	void showMsg(string msg);

};