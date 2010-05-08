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
class Player
{
private:
	short m_troops;//holds amount of units the player gets
	short m_ID; //reflection in order to know what player he is
	short m_conqueredT; //int to tell how many territorys the player has
	//TemplateVector<Territory *> conquered; //list of conquered territories
public:
	Player():m_troops(0),m_ID(0),m_conqueredT(0){}
	//take into account that the starting number of units is depends on players
	Player(short t,short id):m_troops(t),m_ID(id),m_conqueredT(0){}
	short getID(){return this->m_ID;}
	short getTroops(){return this->m_troops;}
	//checks if the player owns the territory
	bool ifOwns(Territory* thatone)
	{
		if(thatone->getOwner()== this->m_ID)
			return true;
		else
			return false;
	}
	//inserts territory into conquered list
	void addLocal(Territory * added)
	{
		if(ifOwns(added))
			printf("player already owns territory\n");
		else{
			added->setOwner(m_ID);
			//conqueredT++;
			//conquered.add(added);
			printf("player owns location\n");
		}
	}
	//set the territory to the enemy players territory
	void removeLocal(Territory *removed, short enemy)
	{
		removed->setOwner(enemy);
		//conqueredT--;
	}	
	//will act as telling the player how many territorys he has	
	//int getListSize(){return conquered.size();}
	//determines how many troops the player has
	void setTroops(int count)
	{
		//check how many countys the player has
		/*if(conqueredT<=minTerri)
			m_troops=minArmys; 
		else
			m_troops=conqueredT/minArmys;*/
		//check if the player controls any continents
		
		//maybe check if the player turns in cards no say ATM
		
	}
	//add troop to a territory (used to init board with players & troops)
	void addToTerritory(Territory *here)
	{
		if(here->getOwner() == m_ID){
			here->addTroopsDeployed(1);
			m_troops--;
		}
	}
	//adds a troop to a territory
	void addTroop(Territory *here)
	{
		if(ifOwns(here))
		{
			here->addTroopsDeployed(m_troops);
			m_troops=0;
		}
		else if(m_troops==0)
			printf("there aren't anymore troops");
		else
			printf("can't add to a territory you don't control");
	}
	//rolls the dice for combat
	void rollDice(int die[],int armys){
		for(int g=0;g<armys;g++){
			int check= random()%dicesides;
			if(check>0)
				die[g]=check;
			else
				die[g]=epicfail;
			}
	}
	//sorts the dice from largest to smallest for combat
	void sortDice(int die[],int numof){
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
				rollDice(def,maxdefD);
			else
				rollDice(def,DefArmys);

			if(AtkArmys>=maxatkD)
				rollDice(atk,maxatkD);
			else
				rollDice(atk,AtkArmys);
			//sorts the die from largest to smallest
			sortDice(atk,maxatkD);
			sortDice(def,maxdefD);		
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
	//checks if the player owns 1 or more continents, & returns the total bonus
	short getContinentBonus(TemplateArray<Territory *> a_board)
	{
		short bonus = 0;

		bool conquered = true;
		for(int i = TERRITORIES_ST_N_AMERICA; i < TERRITORIES_ST_S_AMERICA; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_NA;
		
		conquered = true;
		for(int i = TERRITORIES_ST_S_AMERICA; i < TERRITORIES_ST_EUROPE; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_SA;

		conquered = true;
		for(int i = TERRITORIES_ST_EUROPE; i < TERRITORIES_ST_AFRICA; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_EU;

		conquered = true;
		for(int i = TERRITORIES_ST_AFRICA; i < TERRITORIES_ST_ASIA; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_AF;

		conquered = true;
		for(int i = TERRITORIES_ST_ASIA; i < TERRITORIES_ST_OCEANIA; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_AS;

		conquered = true;
		for(int i = TERRITORIES_ST_OCEANIA; i < TERRITORIES_TOTAL; ++i)
		{
			if(this->m_ID != a_board.get(i)->getOwner())
				conquered = false;
		}
		if(conquered)
			bonus += BONUS_OC;

		return bonus;
	}
	//fortifies troops from territory 1 to territory 2
	void fortify(Territory* a_ter1, Territory* a_ter2, short a_numTroops)
	{
		if(a_ter1->getOwner() == this->m_ID && a_ter2->getOwner() == this->m_ID)
			a_ter1->moveTroopsTo(a_ter2, a_numTroops);
	}
	//give each player a unique identifying color
	void usePlayerColor()
	{
		switch(this->m_ID)
		{
		case PLAYER_ONE:
			glColor3ub(PLAYER_ONE_COLOR);
			break;
		case PLAYER_TWO:
			glColor3ub(PLAYER_TWO_COLOR);
			break;
		case PLAYER_THREE:
			glColor3ub(PLAYER_THREE_COLOR);
			break;
		case PLAYER_FOUR:
			glColor3ub(PLAYER_FOUR_COLOR);
			break;
		case PLAYER_FIVE:
			glColor3ub(PLAYER_FIVE_COLOR);
			break;
		case PLAYER_SIX:
			glColor3ub(PLAYER_SIX_COLOR);
			break;
		}
	}
	//draws the ID's & # of troops within "owned" territories, in Player's unique color
	void drawStats(TemplateArray<Territory *> a_board)
	{
		this->usePlayerColor();
		//adding text to the drawing
		char buffer[BUFFER_SIZE];
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(a_board.get(i)->getOwner() == this->m_ID)
			{
				//displays ID of Territory, NOT player
				sprintf(buffer, "ID: %d\n", a_board.get(i)->getID());
				(a_board.get(i)->getPosition().sum(V2DF(-15,5))).glDrawString(buffer);
				//displays # of troops within territory
				sprintf(buffer, "#T: %d\n", a_board.get(i)->getTroops());
				(a_board.get(i)->getPosition().difference(V2DF(15,5))).glDrawString(buffer);
			}
		}
	}
};