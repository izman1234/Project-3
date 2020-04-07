#ifndef CHARGEMOVES_H
#define CHARGEMOVES_H
#include <string>

class ChargeMoves
{
public:
	//Default constructor
	ChargeMoves();

	//Initialize a FastMove with a name, type, power, and charge energy required
	ChargeMoves(std::string chMName, int chMType, int chMBPower, int chEnergy);

	//Retrieve's a fast move's details
	std::string getName();
	int getChargeMoveBasePwr();
	int getMoveType();
	int getChargeEnergy();

private:
	std::string chargemoveName;	//Charge move's name

	/*
	These ID numbers correspond to each Pokemon type
	0 = Bug
	1 = Dark
	2 = Dragon
	3 = Electric
	4 = Fairy
	5 = Fight
	6 = Fire
	7 = Flying
	8 = Ghost
	9 = Grass
	10 = Ground
	11 = Ice
	12 = Normal
	13 = Poison
	14 = Psychic
	15 = Rock
	16 = Steel
	17 = Water
	*/
	int moveType;		//Charge move's type
	int basePwr;		//Charge move's base power
	int chargeEnergy;	//Charge move's charge energy
};

#endif
