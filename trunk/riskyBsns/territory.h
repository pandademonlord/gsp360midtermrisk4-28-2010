#pragma once

#include "circle.h"
#include "templatearray.h"

class Territory
{
private:
	Circle m_area;
	short m_continentID;
	TemplateArray<Territory *> m_connect;
	short m_ownerID;
	short m_troops_deployed;
public:
	Territory(short a_continentID)
	{
		m_area = Circle();
		m_continentID = a_continentID;
		m_ownerID = OWNER_NONE;
		m_troops_deployed = 0;
	}
	Territory(V2DF a_pos, float a_radius, short a_continentID)
	{
		m_area = Circle(a_pos, a_radius);
		m_continentID = a_continentID;
		m_ownerID = OWNER_NONE;
		m_troops_deployed = 0;
	}
	void setArea(V2DF a_pos, float a_radius)
	{
		m_area.setCenter(a_pos);
		m_area.setRadius(a_radius);
	}
	//adds a connection from this territory to another territory
	void addConnection(Territory* a_territory)
	{
		m_connect.add(a_territory);
	}
	//sets the owner's ID
	void setOwner(short a_ownerID)
	{
		m_ownerID = a_ownerID;
	}
	//sets how many troops are deployed
	void setTroopsDeployed(short a_numTroops)
	{
		m_troops_deployed = a_numTroops;
	}
	//returns the continent to which the territory belongs to
	short getContinent(){return m_continentID;}
	//returns the owner's ID
	short getOwner(){return m_ownerID;}
	//returns how many troops are currently deployed within the territory
	short getTroops(){return m_troops_deployed;}
	void glDraw()
	{
		m_area.glDraw();
	}
	bool isWithin(V2DF click)
	{
		return m_area.isClickable(click);
	}
	~Territory(){}
};