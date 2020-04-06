//Known limitations:
//-The game still prompts you to change Pokemon after all 3 Pokemon have been defeated
#ifndef TRAINER_H
#define TRAINER_H

#include <vector>
#include "FastMoves.h"
#include "ChargeMoves.h"
#include "Pokemon.h"
#include <thread>
#include <chrono>
//CHANGE BY RYO
//4/5/2020
//    -    Replaced #include <chrono> and #include <thread>
#include <conio.h>
#include <Windows.h>
//END OF CHANGE BY RYO

class Trainer
{
public:
	//Default constructor
	Trainer();

	//Initializes a Trainer's name with three Pokemon
	Trainer(std::string name, const Pokemon& poke1, const Pokemon& poke2, const Pokemon& poke3);

	//Retrieves the Trainers' details
	std::string getName();
	int getShieldLeft();
	void reduceShieldAmount();

	//Calculates the damage taken and deducts from the user's Pokemon's HP
	//CHANGE BY RYO
	//4/6/2020 Deleted & after FastMoves
	void takeDamage(FastMoves fMove, Pokemon& userPokemon, Pokemon& enemyPokemon);
	//END OF CHANGE BY RYO
	void takeDamage(ChargeMoves& cMove, Trainer& test, Pokemon& userPokemon, Pokemon& enemyPokemon);

	//The trainer changes out the Pokemon once a Pokemon's health reaches zero
	void changePokemon(Pokemon& defPokemon);

	void battle(FastMoves& fMove, Pokemon& userPokemon, Pokemon& enemyPokemon);

	//CHANGE BY RYO
    //4/4/2020 Completely reworking how the battle function works
    //        -    Deleted the requirement of a Fast Move object and two Pokemon objects as parameters
    //        -    Replaced parameter requirements to two Trainer objects
    void battle(Trainer& player, Trainer& opponent);
    //END OF CHANGE BY RYO

private:
	std::string trainerName;			//Trainer's name
	std::vector<Pokemon> ownedPokemon;	//The trainer's Pokemon (up to 3)
	int shieldLeft;						//The amount of shield uses left
	//CHANGE BY RYO
    //4/5/2020 Added activePokemon and faintedPokemon vectors
    std::vector<Pokemon> activePokemon;    //The trainer's active Pokemon (only 1 at a time)
    std::vector<Pokemon> faintedPokemon; //The trainer's fainted Pokemon (up to 3)
    //END OF CHANGE BY RYO

	float animation_time_remaining;	//Pokemon's animation duration
	float cooldown_time_remaining;	//Pokemon's cooldown time after completing animation
};

#endif
