//Known Limitations:
//
#include "FastMoves.h"

//Default constructor, sets defaults to variables
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
//returns basepower
int FastMoves::getFastMoveBasePwr()
{
	return basePwr;
}
//returns movetype
int FastMoves::getMoveType()
{
	return moveType;
}
//returns energydelta
int FastMoves::getEnergyDelta()
{
	return energyDelta;
}
//returns duration
float FastMoves::getDuration()
{
	return duration;
}
//returns cooldown
float FastMoves::getCooldown()
{
	return cooldown;
}
//returns power
float FastMoves::getPower()
{
    return basePwr;
}
