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
	void takeDamage(FastMoves& fMove, Pokemon& userPokemon, Pokemon& enemyPokemon);
	void takeDamage(ChargeMoves& cMove, Trainer& test, Pokemon& userPokemon, Pokemon& enemyPokemon);

	//The trainer changes out the Pokemon once a Pokemon's health reaches zero
	void changePokemon(Pokemon& defPokemon);

	void battle(FastMoves& fMove, Pokemon& userPokemon, Pokemon& enemyPokemon);

private:
	std::string trainerName;			//Trainer's name
	std::vector<Pokemon> ownedPokemon;	//The trainer's Pokemon (up to 3)
	int shieldLeft;						//The amount of shield uses left

	float animation_time_remaining;	//Pokemon's animation duration
	float cooldown_time_remaining;	//Pokemon's cooldown time after completing animation
};

#endif
