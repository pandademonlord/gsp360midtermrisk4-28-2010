//player class written by Michael Knoche
//Notes: Make sure to account for decimals in the troop count :/
//Always properly test before commiting
#pragma once

#include "territory.h"
#include "card.h"
#include "templatevector.h"

#define dicesides 6
#define epicfail 1
#define maxatkD 3
#define maxdefD 2
#define minArmys 3
#define minTerri 11

class Player
{
private:
	short m_troops;//holds amount of units the player gets
	short m_ID; //reflection in order to know what player he is
	short m_conqueredT; //int to tell how many territorys the player has
	short m_holdCards;//# of cards player is currently holding
public:
	Player():m_troops(0),m_ID(0),m_conqueredT(0), m_holdCards(0){}
	//take into account that the starting number of units is depends on players
	Player(short t,short id):m_troops(t),m_ID(id),m_conqueredT(0){}
	short getID(){return this->m_ID;}
	short getTroops(){return this->m_troops;}
	short getConqueredT(){return this->m_conqueredT;}
	short getNumCards(){return this->m_holdCards;}
	//checks if the player owns the territory
	bool ifOwns(Territory* thatone)
	{
		if(thatone->getOwner()== this->m_ID)
			return true;
		else
			return false;
	}
	//gives player the territory
	void addLocal(Territory * added)
	{
		added->setOwner(m_ID);
		m_conqueredT++;
		//printf("player owns location\n");
	}
	//set the territory to the enemy players territory
	void removeLocal(Territory *removed, short enemy)
	{
		removed->setOwner(enemy);
		m_conqueredT--;
	}	
	//set amount of reinforcement the player gets gives it to troops
	
	//add troop to a territory (used to init board with players & troops)
	void addToTerritory(Territory *here)
	{
		const short addtroop = 1;
		if(ifOwns(here)){
			here->addTroopsDeployed(addtroop);
			m_troops--;
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
	//gives player troops depending on the amount of territory controlled
	short getlocalTroops()
	{
		if(m_conqueredT<=minTerri)
			return minArmys; 
		else
			return m_conqueredT/minArmys;
	}
	void Reinforcements(TemplateArray<Territory *> a_board)
	{

		//check how many territorys the player has
		m_troops+=getlocalTroops();
		//check if the player controls any continents
		m_troops+=getContinentBonus(a_board);
		
		//check if the player turns in cards no say ATM	
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
	//rolls the dice for combat
	void rollDice(short die[],short armys){
		for(int g=0;g<armys;g++){
			short check= random()%dicesides;
			if(check>0)
				die[g]=check;
			else
				die[g]=epicfail;
			}
	}
	//sorts the dice from largest to smallest for combat
	void sortDice(short die[],short numof){
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
	void combat(short DefArmys,short AtkArmys)
	{
		while(DefArmys>0&&AtkArmys>1){
			//holds dice rolls
			short atk[maxatkD];
			short def[maxdefD];
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
	bool isCardSet(Card * a_Card1, Card * a_Card2, Card * a_Card3)
	{
		if(a_Card1->getOwnerID() == this->m_ID &&
		a_Card2->getOwnerID() == this->m_ID &&
		a_Card3->getOwnerID() == this->m_ID)
		{
			short card1, card2, card3;
			card1 = a_Card1->getUnit();
			card2 = a_Card2->getUnit();
			card3 = a_Card3->getUnit();

			//handle the wilds
			if(card1 == CARD_ID_WILD || card2 == CARD_ID_WILD || card3 == CARD_ID_WILD)
				return true;
			//if all cards have same unit
			if(card1 == card2 && card2 == card3)
				return true;
			//if 1 card of each unit
			if(card1 == CARD_ID_SOLDIER || card2 == CARD_ID_SOLDIER || card3 == CARD_ID_SOLDIER)
			{
				if(card1 == CARD_ID_HORSEMAN || card2 == CARD_ID_HORSEMAN || card3 == CARD_ID_HORSEMAN)
				{
					if(card1 == CARD_ID_CANNON || card2 == CARD_ID_CANNON || card3 == CARD_ID_CANNON)
						return true;
				}
			}
		}
		return false;
	}
	bool terCard(Card * a_card, TemplateArray<Territory *> a_board)
	{
		bool extraTroops = false;
		if(a_card->getOwnerID() == a_board.get(a_card->getCardID())->getOwner())
		{
			a_board.get(a_card->getCardID())->addTroopsDeployed(2);
			extraTroops = true;
		}
		return extraTroops;
	}
	void addBonusTroops(short a_bonus)
	{
		if(a_bonus > 0)
			this->m_troops += a_bonus;
	}
	//checks if player owns a set
	bool ownSet(TemplateArray<Card *> a_deck)
	{
		//no set is possible without at least 3 cards
		if(this->m_holdCards < CARD_NUM_IN_SET)
			return false;

		//save array of all owned cards for testing
		TemplateArray<Card *> ownedCrds;
		for(int i = 0; i < a_deck.size(); ++i)
		{
			if(a_deck.get(i)->getOwnerID() == this->m_ID)
				ownedCrds.add(a_deck.get(i));
		}
		//if own 3 cards, check if they make a valid set
		if(this->m_holdCards == CARD_NUM_IN_SET)
			return this->isCardSet(ownedCrds.get(0), ownedCrds.get(1), ownedCrds.get(2));
		else if (this->m_holdCards = CARD_NUM_IN_SET + 1)
		{
			for(int i = 0; i < CARD_NUM_IN_SET; ++i)
			{
				//0,1,2
				//1,2,3
				//2,3,0
				if(this->isCardSet(a_deck.get((i)%this->m_holdCards), a_deck.get((i+1)%this->m_holdCards), a_deck.get((i+2)%this->m_holdCards)))
					return true;
			}
			return false;
		}
		//if holding 5 or more cards, set EXISTS
		return true;
	}
};