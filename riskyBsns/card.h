//Territory class written by Andrew Vitari
#pragma once

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
		this->m_unitID = a_unit;
		this->m_territoryID = a_territoryID;
		this->m_ID = a_ID;
		this->m_ownerID = OWNER_NONE;
	}
	short getUnit(){return this->m_unitID;}
	short getCardID(){return this->m_ID;}
	short getTerritoryID(){return this->m_territoryID;}
	void setOwnerID(short a_ID)
	{
		this->m_ownerID = a_ID;
	}
	short getOwnerID(){return this->m_ownerID;}
	void reshuffle(){this->m_ownerID = OWNER_NONE;}	
};