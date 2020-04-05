#include "Trainer.h"
#include <iostream>
#include <algorithm>
#include <math.h>

//Default constructor
Trainer::Trainer()
{
	trainerName = "";
	shieldLeft = 2;
}

/*
Initializes a Trainer's:
Name
First Pokemon
Second Pokemon
Third Pokemon
*/
Trainer::Trainer(std::string name, const Pokemon& poke1, const Pokemon& poke2, const Pokemon& poke3)
{
	trainerName = name;
	shieldLeft = 2;
	ownedPokemon.push_back(poke1);
	ownedPokemon.push_back(poke2);
	ownedPokemon.push_back(poke3);
}

//Retrieve details about the trainer and their shield uses left
std::string Trainer::getName()
{
	return trainerName;
}
int Trainer::getShieldLeft()
{
	return shieldLeft;
}

/*
Purpose: Reduce the amount of shields the trainer has after using one to block an enemy's charge move
Precondition: Nothing
Postcondition: Reduce the amount of shields by 1*/
void Trainer::reduceShieldAmount()
{
	shieldLeft--;
}

/*
Purpose: Deal damage to the defending Pokemon
Precondition: The move that is being used, the trainer that owns the defending Pokemon (if the move being used is a charge move),
the attacking Pokemon, and the defending Pokemon
Postcondition: */
void Trainer::takeDamage(FastMoves& fMove, Pokemon& defPokemon, Pokemon& atkPokemon)
{
	int TotalDamage;
	float Multiplier;
	float cATK_attacker;
	float cDEF_defender;
	atkPokemon.raiseCurrentEnergy(fMove);
	std::cout << atkPokemon.getName() << " used " << fMove.getName() << "!" << std::endl;

	// CHANGE BY AARON

	// Moved the line below from here:
	// std::cout << defPokemon.getName() << " now has " << defPokemon.getHP() << " HP!" << std::endl;

	Multiplier = atkPokemon.calcMultiplier(atkPokemon, defPokemon, fMove);
	cATK_attacker = (atkPokemon.getBatk() + atkPokemon.getIatk()) * atkPokemon.getCPM(atkPokemon.getLvl());
	cDEF_defender = (defPokemon.getBdef() + defPokemon.getIdef()) * defPokemon.getCPM(defPokemon.getLvl());

	TotalDamage = floor(0.5 * fMove.getFastMoveBasePwr() * (cATK_attacker / cDEF_defender) * Multiplier) + 1;
	defPokemon.calcHP(TotalDamage);

	std::cout << defPokemon.getName() << " now has " << defPokemon.getHP() << " HP!" << std::endl;
	// to here.
	// This way it actually prints out the HP after the damage was subtracted instead of before.

	// END OF CHANGE BY AARON

	changePokemon(defPokemon);
}
void Trainer::takeDamage(ChargeMoves& cMove, Trainer& trainer, Pokemon& defPokemon, Pokemon& atkPokemon)
{
	int TotalDamage = 0;
	float Multiplier;
	float cATK_attacker;
	float cDEF_defender;
	char yesNo;
	std::cout << atkPokemon.getName() << " used " << cMove.getName() << "!" << std::endl;

	Multiplier = atkPokemon.calcMultiplier(atkPokemon, defPokemon, cMove);
	cATK_attacker = (atkPokemon.getBatk() + atkPokemon.getIatk()) * atkPokemon.getCPM(atkPokemon.getLvl());
	cDEF_defender = (defPokemon.getBdef() + defPokemon.getIdef()) * defPokemon.getCPM(defPokemon.getLvl());
	if (atkPokemon.getCurrentEnergy() + cMove.getChargeEnergy() >= 0)
	{
		if (trainer.getShieldLeft() > 0)
		{
			std::cout << "Would you like to use a shield to block this charge move? (y/n)" << std::endl;
			std::cin >> yesNo;
			if (yesNo == 'y')
			{
				std::cout << cMove.getName() << " was blocked by " << trainer.getName() << "'s shield!" << std::endl;
				trainer.reduceShieldAmount();
				TotalDamage = 0;
			}
			else
			{
				if (Multiplier > 1.2)
					std::cout << "It was super-effective!" << std::endl;
				else if (Multiplier < 0.83)
					std::cout << "It wasn't very effective..." << std::endl;
				TotalDamage = floor(0.5 * cMove.getChargeMoveBasePwr() * (cATK_attacker / cDEF_defender) * Multiplier) + 1;
			}
		}
		else
		{
			if (Multiplier > 1.2)
				std::cout << "It was super-effective!" << std::endl;
			else if (Multiplier < 0.83)
				std::cout << "It wasn't very effective..." << std::endl;
			TotalDamage = floor(0.5 * cMove.getChargeMoveBasePwr() * (cATK_attacker / cDEF_defender) * Multiplier) + 1;
		}
	}
	else
	{
		TotalDamage = 0;
		std::cout << atkPokemon.getName() << " does not have enough energy to use this charge move!" << std::endl;
	}

	defPokemon.calcHP(TotalDamage);
	std::cout << defPokemon.getName() << " now has " << defPokemon.getHP() << " HP!" << std::endl;
	changePokemon(defPokemon);
}

/*
Purpose: Changes out a Pokemon once the Pokemon in battle faints
Precondition: The defending Pokemon in battle
Postcondition: if the defending Pokemon's HP reaches 0, the Trainer is prompted to swap out the fainted Pokemon
*/
void Trainer::changePokemon(Pokemon& defPokemon)
{
	int indexOfPokemon;
	if (defPokemon.getHP() <= 0)
	{
		for (size_t c = 0; c < ownedPokemon.size() - 1; c++)
		{
			if (defPokemon == ownedPokemon[c])
				ownedPokemon.erase(ownedPokemon.begin() + c - 1);
		}
		std::cout << "Your Pokemon fainted! Choose another Pokemon to send out: (Enter a number)" << std::endl;
		for (size_t c = 0; c < ownedPokemon.size() - 1; c++)
			std::cout << c + 1<< " - " << ownedPokemon[c].getName() << std::endl;

		std::cin >> indexOfPokemon;

		std::cout << "You sent out " << ownedPokemon[indexOfPokemon - 1].getName() << "!" << std::endl;
	}
}

void Trainer::battle(FastMoves& fMove, Pokemon& userPokemon, Pokemon& enemyPokemon)
{
	int duration = fMove.getDuration() * 1000;
	int cooldown = fMove.getCooldown() * 1000;
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
	takeDamage(fMove, userPokemon, enemyPokemon);
	std::this_thread::sleep_for(std::chrono::milliseconds(cooldown));
}
