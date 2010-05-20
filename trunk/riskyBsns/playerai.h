#pragma once

#include "player.h"
#include "random.h"

class PlayerAI : public Player
{
private:
	//whether or not AI player chooses to ATK
	short m_toAttack;
public:
	PlayerAI(short t,short id) : Player(t, id)
	{
		m_toAttack = 0;
	}
	bool isAI(){return true;}
	//decide whether or not to continue to randomly attack
	bool continueAttack()
	{
		m_toAttack = random() % 2;
		if(m_toAttack == true)
			return true;
		else
			return  false;
	}
	//returns ID of randomly selected un-owned territory to claim
	short getClaimID(TemplateArray<Territory*> a_board)
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(a_board.get(i)->getOwner() == OWNER_NONE)
				numOfValidOptions++;
		}
		short randTer = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(a_board.get(i)->getOwner() == OWNER_NONE)
			{
				if(randTer == counter)
					return a_board.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//returns ID of randomly selected self-owned territory to add 1 troop to
	short getPlaceID(TemplateArray<Territory*> a_board)
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->isConnectedToEnemy())
				numOfValidOptions++;
		}
		short randTer = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->isConnectedToEnemy())
			{
				if(randTer == counter)
					return a_board.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//randomly pick a territory to attack with, pass the board and the AI's ID
	short getAtkOriginID(TemplateArray<Territory*> a_board)
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToEnemy())
				numOfValidOptions++;
		}
		short randAlly = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToEnemy())
			{
				if(randAlly == counter)
					return a_board.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//pick a territory to attack by passing it the board and the result pickAttackingTer()
	short getAtkTargetID(TemplateArray<Territory*> a_board, short a_attackingTerID)
	{
		return a_board.get(a_attackingTerID)->getRandEnemyTerritoryID();
	}
	//returns ID of randomly selected ally-owned ter connected to enemy
	short getFortOriginID(TemplateArray<Territory*> a_board)
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToAlly())
				numOfValidOptions++;
		}
		short randAlly = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < a_board.size(); ++i)
		{
			if(this->ifOwns(a_board.get(i)) && a_board.get(i)->haveTroopsToAttackFority() && a_board.get(i)->isConnectedToAlly())
			{
				if(randAlly == counter)
					return a_board.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//returns ID of randomly selected ally-owned ter connected to ter with a_ID
	short getFortTargetID(TemplateArray<Territory*> a_board, short a_ID)
	{
		return a_board.get(a_ID)->getRandAllyTerritoryID();
	}
	//returns radomly selected # of troops to take from ter with ID of a_ID
	short getFortTroops(TemplateArray<Territory*> a_board, short a_ID)
	{
		return random() % (a_board.get(a_ID)->getTroops() - 1);
	}
};
