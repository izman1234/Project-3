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
