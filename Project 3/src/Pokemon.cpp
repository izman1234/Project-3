#include "Pokemon.h"
#include <math.h>

//Default constructor
Pokemon::Pokemon()
{
	pokemonName = "MissingNo.";
	totalHP = 1;
	currentHP = 1;
	lvl = 1;

	baseATK = 0;
	baseDEF = 0;
	baseSTA = 0;

	ivATK = 0;
	ivDEF = 0;
	ivSTA = 0;

	pType1 = -1;
	pType2 = -1;

	FastMoves fMDefault;
	ChargeMoves cMDefault1;
	ChargeMoves cMDefault2;

	fMoveList[0] = fMDefault;
	chMoveList[0] = cMDefault1;
	chMoveList[1] = cMDefault2;

	currentEnergy = 0;
}

/*
Initializes a Pokemon's:
Name
Level
Base attack
Base defense
Base stamina
IV attack
IV defense
IV stamina
Type ID 1
*/
Pokemon::Pokemon(const std::string& pokeName, const int& level, const int& baseAttack, const int& baseDefense, const int& baseStamina,
	const int& ivAttack, const int& ivDefense, const int& ivStamina, const int& typeNum1)
{
	pokemonName = pokeName;
	totalHP = floor((baseStamina + ivStamina) * CPM[(level * 2) - 1]);
	currentHP = totalHP;
	lvl = level;

	baseATK = baseAttack;
	baseDEF = baseDefense;
	baseSTA = baseStamina;

	ivATK = ivAttack;
	ivDEF = ivDefense;
	ivSTA = ivStamina;

	pType1 = typeNum1;
	pType2 = -1;

	FastMoves fMDefault;
	ChargeMoves cMDefault1;
	ChargeMoves cMDefault2;

	fMoveList[0] = fMDefault;
	chMoveList[0] = cMDefault1;
	chMoveList[1] = cMDefault2;

	currentEnergy = 0;
}

/*
Initializes a Pokemon's:
Name
Level
Base attack
Base defense
Base stamina
IV attack
IV defense
IV stamina
Type ID 1
Type ID 2
*/
Pokemon::Pokemon(const std::string& pokeName, const int& level, const int& baseAttack, const int& baseDefense, const int& baseStamina,
	const int& ivAttack, const int& ivDefense, const int& ivStamina, const int& typeNum1, const int& typeNum2)
{
	pokemonName = pokeName;
	totalHP = floor((baseStamina + ivStamina) * CPM[(level * 2) - 1]);
	currentHP = totalHP;
	lvl = level;

	baseATK = baseAttack;
	baseDEF = baseDefense;
	baseSTA = baseStamina;

	ivATK = ivAttack;
	ivDEF = ivDefense;
	ivSTA = ivStamina;

	pType1 = typeNum1;
	pType2 = typeNum2;

	FastMoves fMDefault;
	ChargeMoves cMDefault1;
	ChargeMoves cMDefault2;

	fMoveList[0] = fMDefault;
	chMoveList[0] = cMDefault1;
	chMoveList[1] = cMDefault2;

	currentEnergy = 0;
}

//Retrieves a Pokemon's information
std::string Pokemon::getName()
{
	return pokemonName;
}
int Pokemon::getHP()
{
	return currentHP;
}
int Pokemon::getBatk()
{
	return baseATK;
}
int Pokemon::getBdef()
{
	return baseDEF;
}
int Pokemon::getBsta()
{
	return baseSTA;
}
int Pokemon::getIatk()
{
	return ivATK;
}
int Pokemon::getIdef()
{
	return ivDEF;
}
int Pokemon::getIsta()
{
	return ivSTA;
}
int Pokemon::getLvl()
{
	return lvl;
}
int Pokemon::getCurrentEnergy()
{
	return currentEnergy;
}

//Overloads the = and == operators
Pokemon& Pokemon::operator=(const Pokemon& poke1)
{
	return *this;
}
bool operator==(const Pokemon& poke1, const Pokemon& poke2)
{
	if (poke1 == poke2)
		return true;
	else
		return false;
}

/*
Purpose: Calculate the damage done to a Pokemon's HP
Precondition: The amount of damage done
Postcondition: Decrease the Pokemon's HP by the total damage done and return the HP
*/
int Pokemon::calcHP(int totalDamage)
{
	currentHP -= totalDamage;
	return currentHP;
}

/*
Purpose: Get the CPM of the Pokemon
Precondition: Pokemon's level
Postcondition: Return the CPM of the Pokemon at that given level
*/
double Pokemon::getCPM(int pokelvl)
{
	return CPM[pokelvl - 1];
}

/*
Purpose: Raise the Pokemon's current energy level after using a fast move
Precondition: FastMoves object
Postcondition: if the currentEnergy <= maxEnergy, then add the energy delta of the fast move to currentEnergy
			   and makes sure that currentEnergy does not surpass maxEnergy value
*/
void Pokemon::raiseCurrentEnergy(FastMoves& fmove)
{
	if (currentEnergy <= maxEnergy)
	{
		currentEnergy += fmove.getEnergyDelta();
		if (currentEnergy > maxEnergy)
			currentEnergy = maxEnergy;
	}
	else
		currentEnergy = maxEnergy;
}

/*
Purpose: Decrease the current energy level after using a charge move
Precondition: ChargeMoves object
Postcondition: Decrease the current energy level by the required amount of energy by the charge move
			   and make sure the current energy level doesn't go below 0
*/
void Pokemon::decreaseCurrentEnergy(ChargeMoves& cmove)
{

	// CHANGE BY AARON:

	// I just changed the - to + since when I tested the function, it added energy instead of subtracting.
	// This was because the "Charge Energy" of a ChargeMove is already a negative integer.
	// We were basically subtracting a negative, so I changed it to adding a negative to make it correct.

	/*
	if (currentEnergy - cmove.getChargeEnergy() < 0)
		currentEnergy = 0;
	else
		currentEnergy -= cmove.getChargeEnergy();

	*/

	if (currentEnergy + cmove.getChargeEnergy() < 0)
		currentEnergy = 0;
	else
		currentEnergy += cmove.getChargeEnergy();

	// END OF CHANGE BY AARON
}

/*
Purpose: Adds fast moves to a Pokemon
Precondition: FastMoves object
Postcondition: Add a FastMoves object to a Pokemon's list of FastMoves
*/
void Pokemon::addFMoves(const FastMoves& fMove1)
{
	fMoveList[0] = fMove1;
}

/*
Purpose: Adds charge moves to a Pokemon
Precondition: ChargeMoves object
Postcondition: Add a ChargeMoves object to a Pokemon's list of ChargeMoves
*/
void Pokemon::addChMoves(const ChargeMoves& chMove1)
{
	chMoveList[0] = chMove1;
}

/*
Purpose: Adds charge moves to a Pokemon
Precondition: ChargeMoves object
Postcondition: Add ChargeMoves objects to a Pokemon's list of ChargeMoves
*/
void Pokemon::addChMoves(const ChargeMoves& chMove1, const ChargeMoves& chMove2)
{
	chMoveList[0] = chMove1;
	chMoveList[1] = chMove2;
}

//Purpose: Calculate damage multiplier, return multiplier
//Precondtion : user's pokemon, enemy's pokemon, the move that is being used
//Post condition : Use switch case statements / if statements for each type ID
float Pokemon::calcMultiplier(Pokemon& poke1, Pokemon& poke2, FastMoves& fmove)
{
	float currentMultiplier = 1;
	if (poke1.pType1 == fmove.getMoveType() || poke1.pType2 == fmove.getMoveType())
	{
		currentMultiplier *= 1.2;
	}

	if (fmove.getMoveType() == 0)	//Effectiveness for Bug type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1.6, 1, 1, .625, .625, .625, .625, .625, 1.6, 1, 1, 1, .625, 1.6, 1, .625, 1};

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 1)	//Effectiveness for Dark type moves
	{
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
		float typeMultipliers[18] =
		{ 1, .625, 1, 1, .625, .625, 1, 1, 1.6, 1, 1, 1, 1, 1, 1.6, 1, 1, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 2)	//Effectiveness for Dragon type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1.6, 1, .391, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 3)	//Effectiveness for Electric type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, .625, .625, 1, 1, 1, 1.6, 1, .625, .391, 1, 1, 1, 1, 1, 1, 1.6 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 4)	//Effectiveness for Fairy type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1.6, 1.6, 1, 1, 1.6, .625, 1, 1, 1, 1, 1, 1, .625, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 5)	//Effectiveness for Fighting type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1.6, 1, 1, .625, 1, 1, .625, .391, 1, 1, 1.6, 1.6, .625, .625, 1.6, 1.6, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 6)	//Effectiveness for Fire type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, .625, 1, 1, 1, .625, 1, 1, 1.6, 1, 1.6, 1, 1, 1, .625, 1.6, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 7)	//Effectiveness for Flying type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, 1, .625, 1, 1.6, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, .625, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 8)	//Effectiveness for Ghost type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 0.625, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, .391, 1, 1.6, 1, 1, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 9)	//Effectiveness for Grass type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1, .625, 1, 1, 1, .625, .625, 1, .625, 1.6, 1, 1, .625, 1, 1.6, .625, 1.6 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 10)	//Effectiveness for Ground type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1, 1, 1.6, 1, 1, 1.6, .391, 1, .625, 1, 1, 1, 1.6, 1, 1.6, 1.6, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 11)	//Effectiveness for Ice type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1.6, 1, 1, 1, .625, 1.6, 1, 1.6, 1.6, .625, 1, 1, 1, 1, .625, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 12)	//Effectiveness for Normal type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1, 1, 1, 1, .391, 1, 1, 1, 1, 1, 1, .625, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 13)	//Effectiveness for Poison type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1.6, 1, 1, 1, .625, 1.6, .625, 1, 1, .625, 1, .625, .391, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 14)	//Effectiveness for Psychic type moves
	{
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
		float typeMultipliers[18] =
		{ 1, .391, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1, 1, 1.6, .625, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 15)	//Effectiveness for Rock type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, 1, 1, 1, .625, 1.6, 1.6, 1, 1, .625, 1.6, 1, 1, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 16)	//Effectiveness for Steel type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1.6, .625, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (fmove.getMoveType() == 17)	//Effectiveness for Water type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, .625, 1, 1, 15, 1.6, 1, 1, .625, 1.6, 1, 1, 1, 1, 1.6, 1, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}

	return currentMultiplier;
}
float Pokemon::calcMultiplier(Pokemon& poke1, Pokemon& poke2, ChargeMoves& cmove)
{
	float currentMultiplier = 1;
	if (poke1.pType1 == cmove.getMoveType() || poke1.pType2 == cmove.getMoveType())
	{
		currentMultiplier *= 1.2;
	}

	if (cmove.getMoveType() == 0)	//Effectiveness for Bug type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1.6, 1, 1, .625, .625, .625, .625, .625, 1.6, 1, 1, 1, .625, 1.6, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 1)	//Effectiveness for Dark type moves
	{
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
		float typeMultipliers[18] =
		{ 1, .625, 1, 1, .625, .625, 1, 1, 1.6, 1, 1, 1, 1, 1, 1.6, 1, 1, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 2)	//Effectiveness for Dragon type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1.6, 1, .391, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 3)	//Effectiveness for Electric type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, .625, .625, 1, 1, 1, 1.6, 1, .625, .391, 1, 1, 1, 1, 1, 1, 1.6 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 4)	//Effectiveness for Fairy type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1.6, 1.6, 1, 1, 1.6, .625, 1, 1, 1, 1, 1, 1, .625, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 5)	//Effectiveness for Fighting type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1.6, 1, 1, .625, 1, 1, .625, .391, 1, 1, 1.6, 1.6, .625, .625, 1.6, 1.6, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 6)	//Effectiveness for Fire type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, .625, 1, 1, 1, .625, 1, 1, 1.6, 1, 1.6, 1, 1, 1, .625, 1.6, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 7)	//Effectiveness for Flying type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, 1, .625, 1, 1.6, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, .625, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 8)	//Effectiveness for Ghost type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 0.625, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, .391, 1, 1.6, 1, 1, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 9)	//Effectiveness for Grass type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1, .625, 1, 1, 1, .625, .625, 1, .625, 1.6, 1, 1, .625, 1, 1.6, .625, 1.6 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 10)	//Effectiveness for Ground type moves
	{
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
		float typeMultipliers[18] =
		{ .625, 1, 1, 1.6, 1, 1, 1.6, .391, 1, .625, 1, 1, 1, 1.6, 1, 1.6, 1.6, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 11)	//Effectiveness for Ice type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1.6, 1, 1, 1, .625, 1.6, 1, 1.6, 1.6, .625, 1, 1, 1, 1, .625, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 12)	//Effectiveness for Normal type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1, 1, 1, 1, .391, 1, 1, 1, 1, 1, 1, .625, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 13)	//Effectiveness for Poison type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1.6, 1, 1, 1, .625, 1.6, .625, 1, 1, .625, 1, .625, .391, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 14)	//Effectiveness for Psychic type moves
	{
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
		float typeMultipliers[18] =
		{ 1, .391, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1, 1, 1.6, .625, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 15)	//Effectiveness for Rock type moves
	{
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
		float typeMultipliers[18] =
		{ 1.6, 1, 1, 1, 1, .625, 1.6, 1.6, 1, 1, .625, 1.6, 1, 1, 1, 1, .625, 1 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 16)	//Effectiveness for Steel type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1.6, .625, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}
	else if (cmove.getMoveType() == 17)	//Effectiveness for Water type moves
	{
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
		float typeMultipliers[18] =
		{ 1, 1, .625, 1, 1, 15, 1.6, 1, 1, .625, 1.6, 1, 1, 1, 1, 1.6, 1, .625 };

		if (poke2.pType2 != -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1] * typeMultipliers[poke2.pType2];
		else if (poke2.pType2 == -1 && poke2.pType1 != -1)
			currentMultiplier = currentMultiplier * typeMultipliers[poke2.pType1];
		else
			currentMultiplier = currentMultiplier * 1;
	}

	return currentMultiplier;
}
