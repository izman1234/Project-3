#include "Trainer.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <windows.h>

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
Purpose: Changes out a Pokemon once the Pokemon in battle faints
Precondition: The defending Pokemon in battle
Postcondition: if the defending Pokemon's HP reaches 0, the Trainer is prompted to swap out the fainted Pokemon
*/
void Trainer::changePokemon(Pokemon& defPokemon)
{
	int indexOfPokemon;
	if (defPokemon.getHP() <= 0)
	{
		for (int c = 0; c < ownedPokemon.size() - 1; c++)
		{
			if (defPokemon == ownedPokemon[c])
				ownedPokemon.erase(ownedPokemon.begin() + c - 1);
		}
		std::cout << "Your Pokemon fainted! Choose another Pokemon to send out: (Enter a number)" << std::endl;
		for (int c = 0; c < ownedPokemon.size() - 1; c++)
			std::cout << c + 1<< " - " << ownedPokemon[c].getName() << std::endl;

		std::cin >> indexOfPokemon;

		std::cout << "You sent out " << ownedPokemon[indexOfPokemon - 1].getName() << "!" << std::endl;
	}
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
	if (defPokemon.getHP() > 0)
    {
	std::cout << defPokemon.getName() << " now has " << defPokemon.getHP() << " HP!" << std::endl;
		// to here.
	// This way it actually prints out the HP after the damage was subtracted instead of before.

	// END OF CHANGE BY AARON
    }
    else
    {
        std::cout << defPokemon.getName() << " now has 0 HP!" << std::endl;
        changePokemon(defPokemon);
    }

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
	if (defPokemon.getHP() > 0)
    {
	std::cout << defPokemon.getName() << " now has " << defPokemon.getHP() << " HP!" << std::endl;
    }
    else
    {
        std::cout << defPokemon.getName() << " now has 0 HP!" << std::endl;
        changePokemon(defPokemon);
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


//CHANGE BY RYO
//4/4/2020
//    -    Started reworking the logic behind looping
//4/5/2020
//Purpose: Keep running battle until either trainer's Pokemon are all wiped out
/*void Trainer::battle(Trainer& player, Trainer& opponent)
{
    //Set active Pokemon (By default, the first Pokemon in ownedPokemon[] will be chosen as the active Pokemon
    bool isStartOfBattle = true;
    if (isStartOfBattle == true)
    {
        player.activePokemon[0] == player.ownedPokemon[0];
    }

    //Arrays for durations and cooldowns of fast moves for the player's and opponent's Pokemon
    int player_Duration[3];
    int player_Cooldown[3];
    int enemy_Duration[3];
    int enemy_Cooldown[3];

    //Sets the durations and cooldowns for all of Pokemon in each player's possession
    //and initializes them in indexes respective to the indexes of the Pokemon in ownedPokemon[].
    //The values will be an integer and the
    for (int i = 0; i < player.ownedPokemon.size() - 1; i++)
    {
        player_Duration[i] = player.ownedPokemon[i].getFMove().getDuration() * 1000;
        player_Cooldown[i] = player.ownedPokemon[i].getFMove().getCooldown() * 1000;
        enemy_Duration[i] = opponent.ownedPokemon[i].getFMove().getDuration() * 1000;
        enemy_Cooldown[i] = opponent.ownedPokemon[i].getFMove().getCooldown() * 1000;
    }

    //Continue while loop as long as either of the trainer's Pokemon haven't all fainted
    while (player.faintedPokemon.size() <= 3 || opponent.faintedPokemon.size() <= 3)
    {
        double
        player.takeDamage();

        if (player.activePokemon[0].getHP() <= 0)
        {

        }
        else if (opponent.activePokemon[0].getHP() <= 0)
        {

        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(userDuration));
        //takeDamage(fMove, userPokemon, enemyPokemon);
        //std::this_thread::sleep_for(std::chrono::milliseconds(userCooldown));
    }
} */
//END OF CHANGE BY RYO

Trainer Battle(Trainer& Player1,Trainer& Player2)
{
    //attack index fast
    //  fast attack - 0
    //  charge attack 1 - 2
    //  charge attack 2 - 2

    int Player1Animation = 0;
    int Player1cooldown = 0;
    bool player1ReadyToAttack = false;
    int Player1MoveSelection = 0;


    int Player2Animation = 0;
    int Player2cooldown = 0;
    bool player2ReadyToAttack = false;
    int Player2MoveSelection = 0;

    int step = 10;//milli sec duration of step between iterations of loop

    Player1.setActivePokemon();//select first poke to use
    Player2.setActivePokemon();//select first poke to use

    while(Player1.hasConsiousPokemon() && Player2.hasConsiousPokemon())
    {
    if(Player1.getownedPokemon()[Player1.getselectedpokemon()].getHP()<=0)
        Player1.setActivePokemon();
    if(Player2.getownedPokemon()[Player2.getselectedpokemon()].getHP()<=0)
        Player2.setActivePokemon();



    //std::cout<<Player1Animation<<"  "<<Player1cooldown<<" "<<Player2Animation<<"  "<<Player2cooldown<<std::endl;

    if(Player1cooldown <= 0)
    {
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
        switch (Player1MoveSelection)
        {
        case 0:
            //fast attack
            Player1Animation = Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getDuration() * 1000;
            Player1cooldown = Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getCooldown() * 1000;
            std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" is attacking with "<<Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getName()<<std::endl;

            PerformFastAttack(Player1,Player2);
            break;
        case 1:
            std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" is attacking with ";
            std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getName()<<std::endl;
            PerformChargeAttack(Player1,Player2);
            break;
        case 2:
            //not implimented in auto battle simulation defaults always to first charge attack
            break;
        }
        std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" Now has "<<Player2.ownedPokemon[Player2.selectedpokemon].getHP()<<" HP remaining"<<std::endl;
        std::cout<<"Current Energy: "<<Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy()<<std::endl;

        if(Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy() >= abs(Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getChargeEnergy()))//if check if current envegy greater than required energy for fast attack 1
        {            Player1MoveSelection = 1;        }//if so set move selection to 1 (will perform charge attack on next turn)
        else
        {            Player1MoveSelection = 0;        }//else set to 0 (will perform fast attack next turn)
    }
    else
    {
        if(Player1Animation<=0)
        {
           Player1cooldown-=step;
        }
        else
        {
            Player1Animation-=step;
        }
    }



    // player two move selection and timing
    if(Player2cooldown <= 0)
    {
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
        switch (Player2MoveSelection)
        {
        case 0:
            //fast attack
            Player2Animation = Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getDuration() * 1000;
            Player2cooldown = Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getCooldown() * 1000;
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" is attacking with "<<Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getName()<<std::endl;

            PerformFastAttack(Player2,Player1);
            break;
        case 1:
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" is attacking with ";
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getName()<<std::endl;
            PerformChargeAttack(Player2,Player1);
            break;
        case 2:
            //not implimented in auto battle simulation defaults always to first charge attack
            break;
        }
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" Now has "<<Player1.ownedPokemon[Player1.selectedpokemon].getHP()<<" HP remaining"<<std::endl;
        std::cout<<"Current Energy: "<<Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy()<<std::endl;

        if(Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy() >= abs(Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getChargeEnergy()))//if check if current envegy greater than required energy for fast attack 1
        {            Player2MoveSelection = 1;        }//if so set move selection to 1 (will perform charge attack on next turn)
        else
        {            Player2MoveSelection = 0;        }//else set to 0 (will perform fast attack next turn)
    }
    else
    {
        if(Player2Animation<=0)
        {
           Player2cooldown-=step;
        }
        else
        {
            Player2Animation-=step;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(step));
    }
    //code for declaring winner
    if(Player1.hasConsiousPokemon())
    {
        return Player1;
    }
    else
    {
        return Player2;
    }

}

bool Trainer::hasConsiousPokemon()
{
    for(int i = 0; i<ownedPokemon.size(); i++)
    {
        if(ownedPokemon[i].getHP()>0)
        {
            return true;
        }
    }
    return false;
}

void Trainer::setActivePokemon()
{
    std::cout<<"-------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Select active pokemon for "<<trainerName<<" form provided list"<<std::endl;

    std::vector<int>possible_Poke;
    for(int i = 0; i<ownedPokemon.size(); i++)
    {
        if(ownedPokemon[i].getHP()>0)
        {
            std::cout<<"\t"<<i<<": "<<ownedPokemon[i].getName()<<std::endl;
            possible_Poke.push_back(i);
        }
    }
    int selection;
    std::cout<<"enter index pokemon to battle with:";
    std::cin>>selection;

    while(!std::count(possible_Poke.begin(),possible_Poke.end(),selection))
    {
        std::cout<<"Index out of range select form provided list:";
        std::cin>>selection;
    }
    selectedpokemon = selection;
}
std::vector<Pokemon> Trainer::getownedPokemon()
{
    return ownedPokemon;
}
int Trainer::getselectedpokemon()
{
    return selectedpokemon;
}
bool PerformChargeAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer)
{
    int damage = 0;
    float mult = 1;

    std::string Decision = "n";
    if(DefendingPlayer.getShieldLeft()>0)
    {
        std::cout<<DefendingPlayer.getName()<<" Do you want to use a sheild to block incoming charge attack you have "<<DefendingPlayer.getShieldLeft()<<" remaining (y/n):";
        std::cin>>Decision;
        while(Decision!="n" and Decision !="y")
        {
            std::cout<<"Error: Invalid Entry Enter 'y' or 'n' "<<std::endl;
            std::cin>>Decision;
        }
    }
    if(Decision == "n")
    {
        mult = AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].GetMultiplier(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon]  ,  AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(0).getMoveType());
        float Catk = (AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getBatk() + AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getIatk()) * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getCPM(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getLvl());
        float Cdef = (DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getBdef()+DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getIdef()) * DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getCPM(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getLvl());
        damage = floor(0.5 * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(0).getChargeMoveBasePwr() * (Catk/Cdef) * mult) + 1;
        DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].calcHP(damage);
    }
    else
    {
        DefendingPlayer.reduceShieldAmount();
    }

    AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].updateCurrentEnergy(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(0).getChargeEnergy());
}
void PerformFastAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer)
{
    int damage = 0;
    float mult = 1;

    mult = AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].GetMultiplier(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon]  ,  AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getMoveType());
    float Catk = (AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getBatk() + AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getIatk()) * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getCPM(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getLvl());
    float Cdef = (DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getBdef()+DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getIdef()) * DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getCPM(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getLvl());
    damage = floor(0.5 * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getFastMoveBasePwr() * (Catk/Cdef) * mult) + 1;

    DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].calcHP(damage);

    AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].updateCurrentEnergy(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getEnergyDelta());

    DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].calcHP(damage);

}