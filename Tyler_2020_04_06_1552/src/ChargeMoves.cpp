#include "ChargeMoves.h"

//Default constructor
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
int ChargeMoves::getChargeMoveBasePwr()
{
	return basePwr;
}
int ChargeMoves::getMoveType()
{
	return moveType;
}
int ChargeMoves::getChargeEnergy()
{
	return chargeEnergy;
}
