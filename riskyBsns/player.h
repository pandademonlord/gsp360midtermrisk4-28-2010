//player class written by Michael Knoche
//Notes: Make sure to account for decimals in the troop count :/
//Always properly test before commiting
#pragma once

#include "territory.h"
#include "card.h"
//#include "templatearray.h"

class Player
{
protected:
	short m_troops;//holds amount of units the player gets
	short m_ID; //reflection in order to know what player he is
	short m_conqueredT; //int to tell how many territorys the player has
	short m_holdCards; //# of cards player is currently holding
public:
	//take into account that the starting number of units is depends on players
	Player(short t,short id)
	{
		this->m_troops = t;
		this->m_ID = id;
		this->m_conqueredT = 0;
		this->m_holdCards = 0;
	}
	short getID(){return this->m_ID;}
	short getTroops(){return this->m_troops;}
	short getConqueredT(){return this->m_conqueredT;}
	short getNumCards(){return this->m_holdCards;}
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
	//checks if the player owns the territory
	bool ifOwns(Territory* thatone)
	{
		if(thatone->getOwner()== this->m_ID)
			return true;
		else
			return false;
	}
	//add troop to a territory (used to init board with players & troops)
	void addToTerritory(Territory *here)
	{
		const short addtroop = 1;
		if(ifOwns(here)){
			here->addTroopsDeployed(addtroop);
			m_troops--;
		}
	}
	//adds troops to the current # of bonus troops still needed to deploy
	void addBonusTroops(short a_bonus)
	{
		if(a_bonus > 0)
			this->m_troops += a_bonus;
	}
	//gives player troops depending on the amount of territory controlled
	short getlocalTroops()
	{
		if(m_conqueredT<=minTerri)
			return minArmys; 
		else
			return m_conqueredT/minArmys;
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
	//gives player troops for # territories occupied & continents conquered
	void Reinforcements(TemplateArray<Territory *> a_board)
	{

		//check how many territorys the player has
		m_troops+=getlocalTroops();
		//check if the player controls any continents
		m_troops+=getContinentBonus(a_board);
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
	//returns true if player has at least 1 territory with 2+ troops connected to enemy
	bool canAttack(TemplateArray<Territory *> a_board)
	{
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)))
			{
				if(a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToEnemy())
				{
					return true;
				}
			}
		}
		return false;
	}
	//returns true if player has at least 1 territory with 2+ troops connected to ally
	bool canFortify(TemplateArray<Territory *> a_board)
	{
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)))
			{
				if(a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToAlly())
				{
					return true;
				}
			}
		}
		return false;
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
				//sprintf(buffer, "ID: %d\n", a_board.get(i)->getID());
				sprintf(buffer, a_board.get(i)->getTerName());
				(a_board.get(i)->getPosition().sum(V2DF(-15,5))).glDrawString(buffer);
				//displays # of troops within territory
				sprintf(buffer, "#T: %d\n", a_board.get(i)->getTroops());
				(a_board.get(i)->getPosition().difference(V2DF(15,5))).glDrawString(buffer);
			}
		}
	}
	//sorts the dice from largest to smallest for combat
	void sortDice(short die[],short numof)
	{
		for(int v=numof;v>0;v--)
		{
			for(int g=numof;g>0;g--)
			{
				if(die[g]>die[g-1])
				{
					int temp= die[g-1];
					die[g-1]=die[g];
					die[g]=temp;
				}
			}
		}
	}
	//is a gameplay state which does the combat
	void combat(Territory * a_ter1, Territory * a_ter2, Player * a_plyr)
	{
		short maxatkD = 3, maxdefD = 2;
		if(a_ter1->getTroops() <= 3)
			maxatkD = a_ter1->getTroops() - 1;
		if(a_ter2->getTroops() < 2)
			maxdefD = 1;

		//holds dice rolls
		short * atk;
		atk = new short[maxatkD];
		short * def;
		def = new short[maxdefD];

		for(int i = 0; i < maxatkD; ++i)
			atk[i] = random() % dicesides;
		for(int i = 0; i < maxdefD; ++i)
			def[i] = random() % dicesides;
		//sorts the die from largest to smallest
		sortDice(atk,maxatkD);
		sortDice(def,maxdefD);

		//compare the dice rolls subtracts the armys
		if(def[0]>=atk[0])
			a_ter1->subtractTroopsDeployed(1);
		else
			a_ter2->subtractTroopsDeployed(1);

		if(maxatkD > 1 && maxdefD > 1)
		{
			if(def[1]>=atk[1])
				a_ter1->subtractTroopsDeployed(1);
			else
				a_ter2->subtractTroopsDeployed(1);
		}

		if(a_ter2->getTroops() == 0)
		{
			//enemy lost a territory
			a_plyr->removeLocal(a_ter2, a_ter1->getOwner());
			//current player gets new territory
			this->addLocal(a_ter2);
			//current player moves troopsinto territory
			a_ter1->moveTroopsTo(a_ter2, maxatkD);
		}

		delete [] atk;
		delete [] def;
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
		if(a_card->getUnit() != CARD_ID_WILD)
		{
			if(a_card->getOwnerID() == a_board.get(a_card->getTerritoryID())->getOwner())
			{
				a_board.get(a_card->getCardID())->addTroopsDeployed(2);
				extraTroops = true;
			}
		}
		return extraTroops;
	}
	//the player draws a random card from the avaiable cards still in the deck
	void drawCardFromDeck(TemplateArray<Card *> a_deck)
	{
		//calc #cards still  in deck
		short allowedToDraw = 0;
		for(int i = 0; i < a_deck.size(); ++i)
		{
			//printf("cardID == %d, owner == %d\n", i, a_deck.get(i)->getOwnerID());
			if(a_deck.get(i)->getOwnerID() == OWNER_NONE)
				allowedToDraw++;
		}
		//if no cards in deck, re-shuffle all discarded cards
		//& re-calc #cards in deck
		while(allowedToDraw == 0)
		{
			for(int i = 0; i < a_deck.size(); ++i)
			{
				if(a_deck.get(i)->getOwnerID() == CARD_DISCARDED)
					a_deck.get(i)->reshuffle();
			}
			allowedToDraw = 0;
			for(int i = 0; i < a_deck.size(); ++i)
			{
				if(a_deck.get(i)->getOwnerID() == OWNER_NONE)
					allowedToDraw++;
			}
		}
		//draw a random card from cards in deck
		//printf("allowedToDraw == %d\n", allowedToDraw);
		short a_card = random() % allowedToDraw;
		//printf("drew card # == %d\n", a_card);
		short a_cardInDeck = 0;
		for(int i = 0; i < a_deck.size(); ++i)
		{
			if(a_deck.get(i)->getOwnerID() == OWNER_NONE)
			{
				if(a_cardInDeck == a_card)
				{
					//printf("drew card had ID == %d\n", i);
					//printf("Player %d drew card with ID == %d\n", (this->m_ID + 1), a_deck.get(i)->getCardID());
					a_deck.get(i)->setOwnerID(this->m_ID);
					m_holdCards++; 
					break;
				}
				else
					a_cardInDeck++;
			}
		}
	}
	//checks if player owns a "set" of cards
	bool ownSet(TemplateArray<Card *> a_deck)
	{
		//no set is possible without at least 3 cards
		if(this->m_holdCards < CARD_NUM_IN_SET)
			return false;
		//if own 5+ cards, set exists
		if(this->m_holdCards > CARD_NUM_IN_SET + 1)
			return true;
		else//holding 3 or 4 cards
		{
			//save array of all owned cards for testing
			TemplateArray<Card *> ownedCrds;
			for(int i = 0; i < a_deck.size(); ++i)
			{
				if(a_deck.get(i)->getOwnerID() == this->m_ID)
					ownedCrds.add(a_deck.get(i));
			}

			if(this->m_holdCards == CARD_NUM_IN_SET)
				return this->isCardSet(ownedCrds.get(0), ownedCrds.get(1), ownedCrds.get(2));
			else
			{
				if(this->isCardSet(ownedCrds.get(0), ownedCrds.get(1), ownedCrds.get(2)))
					return true;
				else if(this->isCardSet(ownedCrds.get(1), ownedCrds.get(2), ownedCrds.get(3)))
					return true;
				else if(this->isCardSet(ownedCrds.get(2), ownedCrds.get(3), ownedCrds.get(0)))
					return true;
				else if(this->isCardSet(ownedCrds.get(3), ownedCrds.get(0), ownedCrds.get(1)))
					return true;
			}
		}
		return false;
	}
	//adds 1 to the current # of cards player is "holding"
	void addCard()
	{
		m_holdCards++;
	}
	//subtracts 1 from the current # of cards player is "holding"
	void removeCard()
	{
		m_holdCards--;
		if(m_holdCards < 0)
			m_holdCards = 0;
	}
	//call if an opponent player is eliminated (current player inherits cards)
	void exchangeCards(Player * a_plyr, TemplateArray<Card *> a_deck)
	{
		//printf("Player %d has eliminated Player %d\n", (this->m_ID + 1), (a_plyr->getID() + 1));
		//give all cards previously owned by a_plyr to this player
		for(int i = 0; i < a_deck.size(); ++i)
		{
			if(a_deck.get(i)->getOwnerID() == a_plyr->getID())
			{
				a_plyr->removeCard();
				a_deck.get(i)->setOwnerID(this->m_ID);
				this->addCard();
			}
		}
	}
	void turnCardsTroops(short a_numSetsTurnedIn)
	{
		//printf("Player %d is turning in a set.\n", (this->getID() + 1));
		switch(a_numSetsTurnedIn)
		{
		case CARD_SET_ONE:
			this->addBonusTroops(BONUS_SET_ONE);
			break;
		case CARD_SET_TWO:
			this->addBonusTroops(BONUS_SET_TWO);
			break;
		case CARD_SET_THREE:
			this->addBonusTroops(BONUS_SET_THREE);
			break;
		case CARD_SET_FOUR:
			this->addBonusTroops(BONUS_SET_FOUR);
			break;
		case CARD_SET_FIVE:
			this->addBonusTroops(BONUS_SET_FIVE);
			break;
		case CARD_SET_SIX:
			this->addBonusTroops(BONUS_SET_SIX);
			break;
		default:
			this->addBonusTroops(BONUS_SET_SIX + ((a_numSetsTurnedIn - CARD_SET_SIX) * BONUS_SET_AFTER_SIX));
		}
	}
	//virtual funcs to be overloaded in the AI class
	//by default, all players are human
	virtual bool isAI(){return false;}
	//only works properly for AI player
	virtual bool continueAttack(){return false;}
	//only works properly for AI player
	virtual short getClaimID(TemplateArray<Territory*> a_board){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getPlaceID(TemplateArray<Territory*> a_board){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getAtkOriginID(TemplateArray<Territory*> a_board){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getAtkTargetID(TemplateArray<Territory*> a_board, short a_ID){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getFortOriginID(TemplateArray<Territory*> a_board){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getFortTargetID(TemplateArray<Territory*> a_board, short a_ID){return OWNER_NONE;}
	//only works properly for AI player
	virtual short getFortTroops(TemplateArray<Territory*> a_board, short a_ID){return OWNER_NONE;}
};