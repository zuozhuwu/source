#include "stdafx.h"

CSolenoidValve::CSolenoidValve() :CValve()
{
	

}

CSolenoidValve::CSolenoidValve(string valveName, ubyte pos0Code, ubyte pos1Code) :CValve(valveName, pos0Code, pos1Code)
{
	
}

CSolenoidValve::~CSolenoidValve()
{

}


void CSolenoidValve::valveCtrl()
{
	if (getPortPres(CValve::valvePort::controlPort) > 0)
	{
		setPos(1);
	}
	else
	{
		setPos(0);      //set to default pos
	}
}
