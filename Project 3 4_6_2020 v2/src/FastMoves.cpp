#include "FastMoves.h"

//Default constructor
FastMoves::FastMoves()
{
	fastmoveName = "";
	moveType = -1;
	basePwr = 0;
	duration = 0;
	energyDelta = 0;
	cooldown = 0;
}

/*
Initializes a Fast Move's:
Name
Type ID
Base power
Duration
Energy Delta
Cooldown
*/
FastMoves::FastMoves(std::string fMName, int fMType, int fMBPower, float fMDuration, int fMEnergyDelta, float fMCooldown)
{
	fastmoveName = fMName;
	moveType = fMType;
	basePwr = fMBPower;
	duration = fMDuration;
	energyDelta = fMEnergyDelta;
	cooldown = fMCooldown;
}

//Retrieves a fast move's details
std::string FastMoves::getName()
{
	return fastmoveName;
}
int FastMoves::getFastMoveBasePwr()
{
	return basePwr;
}
int FastMoves::getMoveType()
{
	return moveType;
}
int FastMoves::getEnergyDelta()
{
	return energyDelta;
}
float FastMoves::getDuration()
{
	return duration;
}
float FastMoves::getCooldown()
{
	return cooldown;
}
