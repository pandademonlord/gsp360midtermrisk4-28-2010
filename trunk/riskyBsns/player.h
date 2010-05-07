//player class written by Michael Knoche
//Notes: Make sure to account for decimals in the troop count :/
//Always properly test before commiting
#pragma once

#include "territory.h"
#include "templatevector.h"


#define dicesides 6
#define epicfail 1
#define maxatkD 3
#define maxdefD 2
#define minArmys 3
#define minTerri 11
////psudo random number generator
////simulates dice roll
class player
{
private:
	short troops;//holds amount of units the player gets
	short ID; //reflection in order to know what player he is
	short conquredT; //int to tell how many territorys the player has
	//TemplateVector<Territory *> conqured; //list of conquered territories
public:
	player():troops(0),ID(0),conquredT(0){}
	//take into account that the starting number of units is depends on players
	player(short t,short id):troops(t),ID(id),conquredT(0){}
	//inserts territory into conquered list
	void addlocal(Territory * added)
	{
		if(ifOwns(added))
			printf("player already owns territory\n");
		else{
			added->setOwner(ID);
			//conquredT++;
			//conqured.add(added);
			printf("player owns location\n");
		}
	}
	//checks if the player owns the territory
	bool ifOwns(Territory* thatone)
	{
		if(thatone->getOwner()==ID)
			return true;
		else
			return false;
	}
	//set the territory to the enemy players territory
	void removelocal(Territory *removed, short enemy)
	{
		removed->setOwner(enemy);
		//conquredT--;
	}	
	//will act as telling the player how many territorys he has	
	//int getlistSize(){return conqured.size();}
	//determines how many troops the player has
	void setroops(int count)
	{
		//check how many countys the player has
		/*if(conquredT<=minTerri)
			troops=minArmys; 
		else
			troops=conquredT/minArmys;*/
		//check if the player controls any continents
		
		//maybe check if the player turns in cards no say ATM
		
	}
	short getroops(){return troops;}
	//adds a troop to a territory
	void addtroop(Territory *here)
	{
		if(ifOwns(here))
		{
			here->addTroopsDeployed(troops);
			troops=0;
		}
		else if(troops==0)
			printf("there aren't anymore troops");
		else
			printf("can't add to that territory you don't control");
	}
	//rolls the dice for combat
	void rolldice(int die[],int armys){
		for(int g=0;g<armys;g++){
			int check= random()%dicesides;
			if(check>0)
				die[g]=check;
			else
				die[g]=epicfail;
			}
	}
	//add troop to a territory 
	void addtoterritory(Territory *here)
	{
		if(here->getOwner()==ID){
			here->addTroopsDeployed(1);
			troops--;
		}
	}
	//sorts the dice from largest to smallest for combat
	void sortdice(int die[],int numof){
		for(int v=numof;v>0;v--){
			for(int g=numof;g>0;g--){
				if(die[g]>die[g-1]){
					int temp= die[g-1];
					die[g-1]=die[g];
					die[g]=temp;
				}
			}
		}
	}

	//is a gameplay state which does the combat
	void combat(int DefArmys,int AtkArmys)
{
		while(DefArmys>0&&AtkArmys>1){
			//holds dice rolls
			int atk[maxatkD];
			int def[maxdefD];
			//rolls dice
			if(DefArmys>=maxdefD)
				rolldice(def,maxdefD);
			else
				rolldice(def,DefArmys);

			if(AtkArmys>=maxatkD)
				rolldice(atk,maxatkD);
			else
				rolldice(atk,AtkArmys);
			//sorts the die from largest to smallest
			sortdice(atk,maxatkD);
			sortdice(def,maxdefD);		
			//compare the dice rolls subtracts the armys
			if(def[0]>=atk[0])
				AtkArmys--;
			else
				DefArmys--;
			if(AtkArmys>1&&DefArmys>1){
				if(def[1]>=atk[1])
					AtkArmys--;
				else
					DefArmys--;
			}
		}
	}
};