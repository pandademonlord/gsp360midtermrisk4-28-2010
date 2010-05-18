#pragma once

#include <stdio.h>	// for printf()
#include "templatearray.h"
#include "random.h"

class Card
{
private:
	short m_ID;
	short m_ownerID;
	short m_unitID;
	short m_territoryID;
public:
	Card(short a_unit, short a_territoryID, short a_ID)
	{
		m_unitID = a_unit;
		m_territoryID = a_territoryID;
		m_ID = a_ID;
		m_ownerID = OWNER_NONE;
	}
	short getUnit(){return this->m_unitID;}
	short getCardID(){return this->m_ID;}
	short getTerritoryID(){return this->m_territoryID;}
	void setOwnerID(short a_ID)
	{
		m_ownerID = a_ID;
	}
	short getOwnerID(){return this->m_ownerID;}
	bool isOwned()
	{
		if(this->m_ownerID == OWNER_NONE)
			return false;
		else
			return true;
	}
	void reshuffle(){m_ownerID = OWNER_NONE;}	
	short drawCard(){return m_ID;}
};