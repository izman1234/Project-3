//Known limitations of Pokemon:
//- All CPM values cannot be used
#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include "FastMoves.h"
#include "ChargeMoves.h"

class Pokemon
{
public:
	//Default constructor
	Pokemon();

	//Initializes a Pokemon object with all base and iv stats, as well as type(s)
	Pokemon(const std::string& pokeName, const int& level, const int& baseAttack, const int& baseDefense, const int& baseStamina,
		const int& ivAttack, const int& ivDefense, const int& ivStamina, const int& typeNum1);
	Pokemon(const std::string& pokeName, const int& level, const int& baseAttack, const int& baseDefense, const int& baseStamina,
		const int& ivAttack, const int& ivDefense, const int& ivStamina, const int& typeNum1, const int& typeNum2);

	//Adds fast and charge moves to the Pokemon
	void addFMoves(const FastMoves& fMove1);
	void addChMoves(const ChargeMoves& chMove1);
	void addChMoves(const ChargeMoves& chMove1, const ChargeMoves& chMove2);

	//Calculate damage multiplier
	float calcMultiplier(Pokemon& poke1, Pokemon& poke2, FastMoves& fmove);
	float calcMultiplier(Pokemon& poke1, Pokemon& poke2, ChargeMoves& cmove);

	//Calculates Pokemon's HP after they took damage
	int calcHP(int totalDamage);

	//Overloads the = and == operators
	Pokemon& operator=(const Pokemon& poke1);
	friend bool operator==(const Pokemon& poke1, const Pokemon& poke2);

	//Retrieve Pokemon's stats and information
	std::string getName();
	int getHP();
	int getBatk();
	int getBdef();
	int getBsta();
	int getIatk();
	int getIdef();
	int getIsta();
	int getLvl();
	double getCPM(int pokelvl);
	void raiseCurrentEnergy(FastMoves& fmove);
	void decreaseCurrentEnergy(ChargeMoves& cmove);
	int getCurrentEnergy();
	//CHANGE BY RYO
    //4/4/2020 Added a function getFMove() which retrieve's a Pokemon's fast move
    FastMoves getFMove();
    //END OF CHANGE BY RYO

    //Changes by tyler
    float GetMultiplier(Pokemon TargetPokemon, int AttackType);
    int updateCurrentEnergy(int deltaEnergy);
    int gettype1();
    int gettype2();
    ChargeMoves getChargemove(int Moveindex);
    //end of changes by Tyler

private:
	std::string pokemonName;	//Pokemon's name
	int totalHP;		//Pokemon's total HP
	int currentHP;		//Pokemon's current HP
	int lvl;			//Pokemon's current level

	int baseATK;		//Pokemon's base attack stat
	int baseDEF;		//Pokemon's base defense stat
	int baseSTA;		//Pokemon's base stamina stat

	int ivATK;			//Pokemon's individual value attack stat
	int ivDEF;			//Pokemon's individual value defense stat
	int ivSTA;			//Pokemon's individual value stamina stat

	const int maxEnergy = 500;	//Pokemon's maximum energy
	int currentEnergy;			//Pokemon's current energy

	int pType1=-1;	//Pokemon's first type
	int pType2=-1;	//Pokemon's second type
	/*These ID numbers correspond to each Pokemon type
	0 = Bug
	1 = Dark
	2 = Dragon
	3 = ElectricpType1
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

	FastMoves fMoveList[1];		//Pokemon can know only 1 fast move at any given time
	ChargeMoves	chMoveList[2];	//Pokemon can know up to 2 charge moves at any given time

	//All of the possible CP multiplier values from level 1 to level 45 (incremented by 0.5 from 1 to 40) according to https://gamepress.gg/pokemongo/cp-multiplier
	const double CPM[84] = {.094, 0.1351374318, 0.16639787, 0.192650919, 0.21573247, 0.2365726613, 0.25572005,
	0.2735303812, 0.29024988, 0.3060573775, 0.3210876, 0.3354450362, 0.34921268, 0.3624577511, 0.3752356,
	0.387592416, 0.39956728, 0.4111935514, 0.4225, 0.4329264091, 0.44310755, 0.4530599591, 0.4627984, 0.472336093,
	0.48168495, 0.4908558003, 0.49985844, 0.508701765, 0.51739395, 0.5259425113, 0.5343543, 0.5426357375,0.5507927,
	0.5588305862, 0.5667545, 0.5745691333, 0.5822789, 0.5898879072, 0.5974, 0.6048236651, 0.6121573 ,0.6194041216,
	0.6265671, 0.6336491432, 0.64065295, 0.6475809666, 0.65443563, 0.6612192524, 0.667934, 0.6745818959, 0.6811649,
	0.6876849038, 0.69414365, 0.70054287, 0.7068842, 0.7131691091, 0.7193991, 0.7255756136, 0.7317, 0.7347410093,
	0.7377695, 0.7407855938, 0.74378943, 0.7467812109, 0.74976104, 0.7527290867, 0.7556855, 0.7586303683,
	0.76156384, 0.7644860647, 0.76739717, 0.7702972656, 0.7731865, 0.7760649616, 0.77893275, 0.7817900548,
	0.784637, 0.7874736075, 0.7903, 0.79530001, 0.8003, 0.8053, 0.81029999, 0.81529999};

	float Type_Multiplier[18][18] =
            {{1,1,1,1,1,0.625,1.6,1.6,1,0.625,0.625,1,1,1,1,1.6,1,1},//BUG
            {1.6,0.625,1,1,1.6,1.6,1,1,0.625,1,1,1,1,1,0.391,1,1,1},//DARK
            {1,1,1.6,0.625,1.6,1,0.625,1,1,0.625,1,1.6,1,1,1,1,1,0.625},//DRAGON
            {1,1,1,0.625,1,1,1,0.625,1,1,1.6,1,1,1,1,1,0.625,1},//ELECTRIC
            {0.625,0.625,1,1,0.391,0.625,1,1,1,1,1,1,1,1.6,1,1,1.6,1},//FAIRY
            {0.625,0.625,1,1,1.6,1,1,1.6,1,1,1,1,1,1,1.6,0.625,1,1},//FIGHT
            {0.625,1,1,1,0.625,1,0.625,1,1,0.625,1.6,0.625,1,1,1,1.6,0.625,1.6},//FIRE
            {0.625,1,1,1.6,1,0.625,1,1,1,0.625,0.391,1.6,1,1,1,1.6,1,1},//FLYING
            {0.625,1.6,1,1,1,0.391,1,1,1.6,1,1,1,0.391,0.625,1,1,1,1},//GHOST
            {1.6,1,1,0.625,1,1,1.6,1.6,1,0.625,0.625,1.6,1,1.6,1,1,1,0.625},//GRASS
            {1,1,1,0.391,1,1,1,1,1,1.6,1,1.6,1,0.625,1,0.625,1,1.6},//GROUND
            {0.625,1,1,1,1,1.6,1.6,1,1,1,1,1,1,1,1,1.6,1.6,1},//ICE
            {1,1,1,1,1,1.6,1,1,0.391,1,1,1,1,1,1,1,1,1},//NORMAL
            {0.625,1,1,1,0.625,0.625,1,1,1,0.625,1.6,1,1,0.625,1.6,1,1,1},//POISON
            {1.6,1.6,1,1,1,0.625,1,1,1.6,1,1,1,1,1,0.625,1,1,1},//PSYCHC
            {1,1,1,1,1,1.6,0.625,0.625,1,1.6,1.6,1,0.625,0.625,1,1,1.6,1.6},//ROCK
            {1,1,1,0.625,0.625,0.625,1.6,1.6,1,0.391,1,1.6,1,1,1.6,1,1,0.625},//STELL
            {1,1,1,1.6,1,1,0.625,1,1,1.6,1,0.625,1,1,1,1,0.625,0.625}};//WATER
};
#endif
