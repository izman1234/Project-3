//Known Limitations:
//
#include "ChargeMoves.h"

//Default constructor, sets defaults to variables
ChargeMoves::ChargeMoves()
{
	chargemoveName = "";
	moveType = -1;
	basePwr = 0;
	chargeEnergy = 0;
}

/*
Initializes a Charge Move's:
Name
Type ID
Base power
Required energy
*/
ChargeMoves::ChargeMoves(std::string chMName, int chMType, int chMBPower, int chEnergy)
{
	chargemoveName = chMName;
	moveType = chMType;
	basePwr = chMBPower;
	chargeEnergy = chEnergy;
}

//Retrieves a charge move's details
std::string ChargeMoves::getName()
{
	return chargemoveName;
}
//returns base power
int ChargeMoves::getChargeMoveBasePwr()
{
	return basePwr;
}
//returns movetype
int ChargeMoves::getMoveType()
{
	return moveType;
}
//returns chargeenergy
int ChargeMoves::getChargeEnergy()
{
	return chargeEnergy;
}
