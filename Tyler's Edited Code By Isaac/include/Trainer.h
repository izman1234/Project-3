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


    //CHANGE BY Tyler
    //4/5/2020 Completely reworking how the battle function works
    friend Trainer Battle(Trainer& Player1,Trainer& Player2);

    bool hasConsiousPokemon();
    void setActivePokemon();
    std::vector<Pokemon> getownedPokemon();
    int getselectedpokemon();
    friend bool PerformChargeAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer);
    friend void PerformFastAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer);
    //END OF CHANGE BY TYLER

private:
	std::string trainerName;			//Trainer's name
	std::vector<Pokemon> ownedPokemon;	//The trainer's Pokemon (up to 3)
	int shieldLeft;						//The amount of shield uses left


    int selectedpokemon;//index of selected pokemon in owned pokemon vector used in tylers verison of battle if version not used delete this variable
};

#endif
