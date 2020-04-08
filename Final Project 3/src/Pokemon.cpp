//Known limitations of Pokemon:
//Known limitations of Pokemon: N/A - Am

//comments checked and added by Ashley MC.

////Purpose:  Create a Pokemon object with default variable declarations. - AM
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
//Purpose:  Create a Pokemon object whichInitializes a Pokemon's: . - AM
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
//Purpose:  Create a Pokemons  object which Initializes a Pokemon's:  - AM
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
    return fMoveList[0]; //returns give fast move from Move list - AM
}

//Retrieves a Pokemon's information
//comments Added by Ashley McIntosh
std::string Pokemon::getName()
{
	return pokemonName; // Returns Pokemon's name - AM
}
int Pokemon::getHP()
{
	return currentHP; // Returns Pokemon's current HP level - AM
}
int Pokemon::getBatk()
{
	return baseATK; // return Pokemon's base attack stat - AM
}
int Pokemon::getBdef()
{
	return baseDEF; // return Pokemon's base defense stat - AM
}
int Pokemon::getBsta()
{
	return baseSTA; // Returns Pokemon's base stamina stat - AM
}
int Pokemon::getIatk()
{
	return ivATK; // returns Pokemon's individual value attack stat - AM
}
int Pokemon::getIdef()
{
	return ivDEF; // returns Pokemon's individual value defense stat - AM
}
int Pokemon::getIsta()
{
	return ivSTA; // returnsPokemon's individual value stamina stat- AM
}
int Pokemon::getLvl()
{
	return lvl; //Returns Pokemon's current level - AM
}
int Pokemon::getCurrentEnergy()
{
	return currentEnergy; //returns Pokemon's current energy - AM
}
//comments ended by Ashley

//Purpose:Overloads the = and == operators
//
Pokemon& Pokemon::operator=(const Pokemon& poke1)
{
	return *this;
}
//This operation not needed in code - AM
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
//Postcondition: float for multiplier to be applied to damage
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
//Comments start by Ashley Mcintosh
int Pokemon::gettype1()
{
    return pType1; //Returns Pokemon's first type - Am
}
int Pokemon::gettype2()
{
    return pType2; //Return Pokemon's second type - Am
}
int Pokemon::updateCurrentEnergy(int deltaEnergy)
{
    currentEnergy+=deltaEnergy;  //Updates current energy for pokemon by returning current energy from delta energy - Am
}
ChargeMoves Pokemon::getChargemove(int Moveindex)
{
    return chMoveList[Moveindex]; //returns given charge moves from move index list - AM
}
//Comments end by Ashley Mc

//End of Code Changes by Tyler
