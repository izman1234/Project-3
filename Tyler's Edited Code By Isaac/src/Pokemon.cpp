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

FastMoves Pokemon::getFMove()
{
    return fMoveList[0];
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

//ADDED BY SKYYSHA CARROLL
//Purpose: To add health to a Pokemon's HP.
//Precondition: The amount of health to be added.
//Postcondition: Increase the Pokemon's HP by addh and return the HP.
int Pokemon::useHealthMove(int addh) //ADDED BY SKYYSHA CARROLL
{
  currentHP += addh;
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
//Changes by Tyler
//Purpose: Calculates Multiplier using 2D array
//Precondition: Pokemon as calling object a target pokemon of pokemon class and the type of the attack
//Postcondition: float for multipler to be applied to damage
float Pokemon::GetMultiplier(Pokemon TargetPokemon, int AttackType)
{
    float Multiplier = 1;
    if((pType1==AttackType)||(pType2==AttackType))
        Multiplier*=1.2;
    if(TargetPokemon.gettype1()>=0)
        Multiplier*=(  Type_Multiplier[AttackType][TargetPokemon.gettype1()]);//[std::find(POKEMON_TYPES.begin(),POKEMON_TYPES.end(),"Bug")][0]           );
    if(TargetPokemon.gettype2()>=0)
        Multiplier*=(  Type_Multiplier[AttackType][TargetPokemon.gettype2()]);//[std::find(POKEMON_TYPES.begin(),POKEMON_TYPES.end(),"Bug")][0]           );

    return Multiplier;
}
int Pokemon::gettype1()
{
    return pType1;
}
int Pokemon::gettype2()
{
    return pType2;
}
int Pokemon::updateCurrentEnergy(int deltaEnergy)
{
    currentEnergy+=deltaEnergy;
}
ChargeMoves Pokemon::getChargemove(int Moveindex)
{
    return chMoveList[Moveindex];
}
//End of Changes by Tyler

//Purpose: Calculate damage multiplier, return multiplier
//Precondtion : user's pokemon, enemy's pokemon, the move that is being used
//Post condition : Use switch case statements / if statements for each type ID
