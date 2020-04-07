#ifndef FASTMOVES_H
#define FASTMOVES_H
#include <string>
class FastMoves
{
public:
	//Create a default FastMove
	FastMoves();

	//Initialize a FastMove with a name, type, power, duration, energy delta, cooldown
	FastMoves(std::string fMName, int fMType, int fMBPower, float fMDuration, int fMEnergyDelta, float fMCooldown);

	//Retrieve's a fast move's details
	std::string getName();
	int getFastMoveBasePwr();
	int getMoveType();
	int getEnergyDelta();
	float getDuration();
	float getCooldown();


	float getPower();


private:
	std::string fastmoveName;	//Fast move's name

	/*These ID numbers correspond to each Pokemon type
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
	int moveType;		//Fast move's type
	int basePwr;		//Fast move's base power
	float duration;		//Fast move's duration
	int energyDelta;	//Fast move's energy delta
	float cooldown;		//Fast move's cooldown
};
#endif
