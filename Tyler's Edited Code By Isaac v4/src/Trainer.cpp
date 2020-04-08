//Known limitations:
//-The game still prompts you to change Pokemon after all 3 Pokemon have been defeated
#include "Trainer.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>


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
Purpose:
Precondition: Nothing
Postcondition: Reduce the amount of shields by 1*/
Trainer Battle(Trainer& Player1,Trainer& Player2)
{
    int Player1MoveSelection = 0;//variable for which move player1 will perform next
    int Player2MoveSelection = 0;//variable for which move player2 will perform next
    int step = 1000;//milli sec duration of step between iterations of loop was used for cooldown and animation durations be for changes to code

    Player1.setActivePokemon();//select first poke to use
    Player2.setActivePokemon();//select first poke to use

    while(Player1.hasConsiousPokemon() && Player2.hasConsiousPokemon())//while loop to continue battle until one trainer no longer has a conscious Poke
    {
    if(Player1.getownedPokemon()[Player1.getselectedpokemon()].getHP()<=0)//checks if current pokemon HP>0 if not call setActive pokemon to select different pokemon with >0 HP
        Player1.setActivePokemon();
    if(Player2.getownedPokemon()[Player2.getselectedpokemon()].getHP()<=0)//Performs same task of checking if HP > 0 for player 2
        Player2.setActivePokemon();

    std::cout<<"-------------------------------------------------------------------------"<<std::endl;//line separating player1s action
    if(Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy() >= abs(Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getChargeEnergy()) || Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy() >= abs(Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(1).getChargeEnergy()))//if check if current envegy greater than required energy for fast attack 1
    {
        std::vector<int> possibleSelection;//variable to store possible moves a pokemon can perform with current energy
        std::cout<<Player1.getName()<<" You have enough Energy to perform a charge attack"<<std::endl;//inform player they can perform a charge move
        std::cout<<"\t0 - Fast attack "<<Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getName()<<" (Delta Energy "<<Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getEnergyDelta()<<")"<<std::endl;
        possibleSelection.push_back(0);//push back 0 for fast move case
        if(Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy() >= abs(Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getChargeEnergy()))//check if player1 pokemon has energy sufficient to perform charge move 1
        {
            std::cout<<"\t1 - Charge attack 1 :"<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getName()<<" (Required Energy "<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getChargeEnergy()<<")"<<std::endl;
            possibleSelection.push_back(1);//push back 1 for charge move 1
        }
        if(Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy() >= abs(Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(1).getChargeEnergy()))//check if player 1 pokemon has energy sufficient for charge move 2
        {
            std::cout<<"\t2 - Charge attack 2 :"<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(1).getName()<<" (Required Energy "<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(1).getChargeEnergy()<<")"<<std::endl;
            possibleSelection.push_back(2);//push back 2 for charge move 2
        }

        std::cout<<"select what move you wish to perform:";//prompt user to select a move form list provided
        std::cin>>Player1MoveSelection;//enter int representing move
        while(!std::count(possibleSelection.begin(),possibleSelection.end(),Player1MoveSelection))//check if move provided is in list of possible moves
        {
            std::cout<<"Index out of range select form provided list:";
            std::cin>>Player1MoveSelection;
        }//END of while loop checking if move selection is valid
    }//end of if statement for determining next move
    else//if player lacks energy to perform either charge move defaults to using fast move
    {
        Player1MoveSelection = 0;//set to zero for fast attack
    }


    switch (Player1MoveSelection)//switch statement which performs a given charge move
    {
    case 0://case where selection = 1 perform fast move
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" is attacking with "<<Player1.ownedPokemon[Player1.selectedpokemon].getFMove().getName()<<std::endl;//
        PerformFastAttack(Player1,Player2);//performs fast move
        break;
    case 1://case where selection = 1 performs charge move one
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" is attacking with ";
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(0).getName()<<std::endl;
        PerformChargeAttack(Player1,Player2,0);//perform charge attack 1
        break;
    case 2://case where selection = 2 performs charge move two
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" is attacking with ";
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getChargemove(1).getName()<<std::endl;
        PerformChargeAttack(Player1,Player2,1);//perform charge move 2
        break;
    }
    std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" Now has "<<Player2.ownedPokemon[Player2.selectedpokemon].getHP()<<" HP remaining"<<std::endl;
    std::cout<<"Current Energy: "<<Player1.ownedPokemon[Player1.selectedpokemon].getCurrentEnergy()<<std::endl;


    std::this_thread::sleep_for(std::chrono::milliseconds(step/2));//causes program to stop for value of step milliseconds / 2 between each set of players moving
    if (Player2.ownedPokemon[Player2.selectedpokemon].getHP()>0)//check if player 2 pokemon is conscious after player ones attack
    {
            std::cout<<"-------------------------------------------------------------------------"<<std::endl;

        if(((Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy()) >= (abs(Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getChargeEnergy()))) || ((Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy()) >= (abs(Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(1).getChargeEnergy()))))//if check if current envegy greater than required energy for fast attack 1
        {
            std::vector<int> possibleSelection;
            std::cout<<Player2.getName()<<" You have enough Energy to perform a charge attack"<<std::endl;
            std::cout<<"\t0 - Fast attack :"<<Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getName()<<" (Delta Energy "<<Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getEnergyDelta()<<")"<<std::endl;
            possibleSelection.push_back(0);
            if(Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy() >= abs(Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getChargeEnergy()))
            {
                std::cout<<"\t1 - Charge attack 1 :"<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getName()<<" (Required Energy "<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getChargeEnergy()<<")"<<std::endl;
                possibleSelection.push_back(1);
            }
            if(Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy() >= abs(Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(1).getChargeEnergy()))
            {
                std::cout<<"\t2 - Charge attack 2 :"<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(1).getName()<<" (Required Energy "<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(1).getChargeEnergy()<<")"<<std::endl;
                possibleSelection.push_back(2);
            }

            std::cout<<"select what move you wish to perform:";
            std::cin>>Player2MoveSelection;
            while(!std::count(possibleSelection.begin(),possibleSelection.end(),Player2MoveSelection))
            {
                std::cout<<"Index out of range select form provided list:";
                std::cin>>Player2MoveSelection;
            }
        }
        else//if player lacks energy to perform either charge move defaults to using fast move
        {
            Player2MoveSelection = 0;//set to zero for fast attack
        }



        switch (Player2MoveSelection)
        {
        case 0:
            //fast attack
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" is attacking with "<<Player2.ownedPokemon[Player2.selectedpokemon].getFMove().getName()<<std::endl;

            PerformFastAttack(Player2,Player1);
            break;
        case 1:
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" is attacking with ";
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(0).getName()<<std::endl;
            PerformChargeAttack(Player2,Player1,0);
            break;
        case 2:
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getName()<<" is attacking with ";
            std::cout<<Player2.ownedPokemon[Player2.selectedpokemon].getChargemove(1).getName()<<std::endl;
            PerformChargeAttack(Player2,Player1,1);
            break;
        }
        std::cout<<Player1.ownedPokemon[Player1.selectedpokemon].getName()<<" Now has "<<Player1.ownedPokemon[Player1.selectedpokemon].getHP()<<" HP remaining"<<std::endl;
        std::cout<<"Current Energy: "<<Player2.ownedPokemon[Player2.selectedpokemon].getCurrentEnergy()<<std::endl;

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(step/2));//causes program to stop for value of step milliseconds between each set of players moving
    }



    //code for declaring winner
    if(Player1.hasConsiousPokemon())//checks if player one has any conscious pokemon left
    {
        return Player1;//if this is true then he is the winner of battle
    }
    else
    {
        return Player2;//if player one has no Pokemon with Hp > 0 then Player2 is the winner
    }

}
/*
Purpose: check if A trainer has a Poke with HP>0
Precondition: Nothing
Postcondition: true if at least on pokemon is conscious*/
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
/*
Purpose: select the pokemon currently active for a trainer
Precondition: Nothing
Postcondition: index of selected pokemon in owned pokemon vector assigned to selected pokemon variable*/
void Trainer::setActivePokemon()
{
    std::cout<<"-------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Select active pokemon for "<<trainerName<<" form provided list"<<std::endl;

    std::vector<int>possible_Poke;//loop to provide options of all owned pokemon with Hp > 0
    for(int i = 0; i<ownedPokemon.size(); i++)//loops through each pokemon in owned pokemon vector
    {
        if(ownedPokemon[i].getHP()>0)//chekcs if pokemon Hp>0
        {
            std::cout<<"\t"<<i<<": "<<ownedPokemon[i].getName()<<std::endl;//print out index and name
            possible_Poke.push_back(i);//add this to the list of possible poke to choose from
        }
    }
    int selection;//var to store user selection
    std::cout<<"enter index pokemon to battle with:";
    std::cin>>selection;

    while(!std::count(possible_Poke.begin(),possible_Poke.end(),selection))//while loop - while index provided by user not in possible poke vector
    {
        std::cout<<"Index out of range select form provided list:";
        std::cin>>selection;
    }
    selectedpokemon = selection;//assign value to selected Poke variable
}
/*
Purpose: return a vector of ownedPokemon*/
std::vector<Pokemon> Trainer::getownedPokemon()//
{
    return ownedPokemon;
}
/*
Purpose: return int index of owned pokemon of the currently active pokemon*/
int Trainer::getselectedpokemon()
{
    return selectedpokemon;
}
/*
Purpose: Have attacking players currently selected pokemon perform the charge attack using provided index on the currently selected poke of defending player
Precondition: Attacking trainer defending trainer and index of the attacking players charge move list they wish to use
Postcondition: if player shields reduce defending player shield count by one and reduce energy of attacking player ,
                if player does not shield apply damage to defending pokemon reduce energy of attacking pokemon  */
bool PerformChargeAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer, int ChargeAtttackIndex)
{
    int damage = 0;
    float mult = 1;
    std::string Decision = "n";//decision of user y if they wish to use shield n if not defaults to n
    if(DefendingPlayer.getShieldLeft()>0)//check id defender has any shields remaining
    {
        std::cout<<DefendingPlayer.getName()<<" Do you want to use a shield to block incoming charge attack you have "<<DefendingPlayer.getShieldLeft()<<" remaining (y/n):";
        std::cin>>Decision;
        while(Decision!="n" && Decision !="y")//checks if input Y or n if not ask to provide another input
        {
            std::cout<<"Error: Invalid Entry Enter 'y' or 'n' "<<std::endl;
            std::cin>>Decision;
        }
    }
    if(Decision == "n")//if player chooses to use shield
    {
        mult = AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].GetMultiplier(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon]  ,  AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(ChargeAtttackIndex).getMoveType());
        float Catk = (AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getBatk() + AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getIatk()) * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getCPM(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getLvl());
        float Cdef = (DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getBdef()+DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getIdef()) * DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getCPM(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getLvl());
        damage = floor(0.5 * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(ChargeAtttackIndex).getChargeMoveBasePwr() * (Catk/Cdef) * mult) + 1;
        DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].calcHP(damage);//calculate damage done then apply it to defending pokemon
    }
    else
    {
        DefendingPlayer.reduceShieldAmount();//if player chooses to block reduce their shield amount by one
    }

    AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].updateCurrentEnergy(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getChargemove(ChargeAtttackIndex).getChargeEnergy());//reduce attacking poke energy
}
/*
Purpose: Attacking players selected poke performs fast attack on defending players selected pokemon
Precondition: Attacking trainer and defending trainer
Postcondition: reduces hp of defending player by calculated amount and increase energy of attacking player by amount dictated by the fast move */
void PerformFastAttack(Trainer& AttakingPlayer, Trainer& DefendingPlayer)
{
    int damage = 0;
    float mult = 1;

    mult = AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].GetMultiplier(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon]  ,  AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getMoveType());
    float Catk = (AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getBatk() + AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getIatk()) * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getCPM(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getLvl());
    float Cdef = (DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getBdef()+DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getIdef()) * DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getCPM(DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].getLvl());
    damage = floor(0.5 * AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getFastMoveBasePwr() * (Catk/Cdef) * mult) + 1;

    DefendingPlayer.ownedPokemon[DefendingPlayer.selectedpokemon].calcHP(damage);//calc damage done by fast move then apply it to defending poke

    AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].updateCurrentEnergy(AttakingPlayer.ownedPokemon[AttakingPlayer.selectedpokemon].getFMove().getEnergyDelta());//add delta energy of fast attack to attacking players hp
}
