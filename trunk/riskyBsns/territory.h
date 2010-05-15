#pragma once

#include "circle.h"
#include "templatearray.h"

class Territory
{
private:
	Circle m_area;
	short m_ID;
	short m_continentID;
	TemplateArray<Territory *> m_connect;
	short m_ownerID;
	short m_troops_deployed;
public:
	void useContinentColor()
	{
		switch(this->m_continentID)
		{
		case CONTINENT_ID_N_AMERICA:
			this->setColor(CONTINENT_COLOR_NA);
			break;
		case CONTINENT_ID_S_AMERICA:
			this->setColor(CONTINENT_COLOR_SA);
			break;
		case CONTINENT_ID_EUROPE:
			this->setColor(CONTINENT_COLOR_EU);
			break;
		case CONTINENT_ID_AFRICA:
			this->setColor(CONTINENT_COLOR_AF);
			break;
		case CONTINENT_ID_ASIA:
			this->setColor(CONTINENT_COLOR_AS);
			break;
		case CONTINENT_ID_OCEANIA:
			this->setColor(CONTINENT_COLOR_OC);
			break;
		}
	}
	Territory(short a_ID, short a_continentID)
	{
		m_area = Circle();
		m_ID = a_ID;
		m_continentID = a_continentID;
		m_ownerID = OWNER_NONE;
		m_troops_deployed = 0;
		this->useContinentColor();
	}
	//sets the clickable size of the territory
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
	//adds troops to the current # deployed
	void addTroopsDeployed(short a_numTroops)
	{
		m_troops_deployed += a_numTroops;
		if(m_troops_deployed < 0)
			m_troops_deployed = 0;
	}
	//subtracts troops deployed from the current # deployed
	void subtractTroopsDeployed(short a_numTroops)
	{
		this->addTroopsDeployed(-1 * a_numTroops);
	}
	//returns the territory's position as a V2D
	V2DF getPosition() {return this->m_area.getCenter();}
	//returns the territory's clickable radius
	short getRadius(){return this->m_area.getRadius();}
	//returns the territory's unique ID
	short getID(){return this->m_ID;}
	//returns the continent to which the territory belongs to
	short getContinent(){return m_continentID;}
	//returns the owner's ID
	short getOwner(){return m_ownerID;}
	//returns how many troops are currently deployed within the territory
	short getTroops(){return m_troops_deployed;}
	//sets the color to display the area
	void setColor(short a_r, short a_g, short a_b)
	{
		this->m_area.setColor(a_r, a_g, a_b);
	}
	//returns the # of existing connections
	short getNumberConnections(){return this->m_connect.size();}
	//checks if the passed territoryis connected to this territory	
	bool isConnectedTo(Territory* a_territory)
	{
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(a_territory == this->m_connect.get(i))
				return true;
		}
		return false;
	}
	//draw the circular clickable area
	void glDraw(){m_area.glDraw();}
	//draws the connections to adjacent territories
	void drawConnections()
	{
		//draw connections toadjacent territories
		glColor3f(COLOR_GREY);
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			glBegin(GL_LINES);
			this->getPosition().glVertex();
			this->m_connect.get(i)->getPosition().glVertex();
			glEnd();
		}
	}
	bool isWithin(V2DF &click)
	{
		return m_area.isClickable(click);
	}
	//moves a_numTroops amt of troops from this territory to a_territory
	void moveTroopsTo(Territory * a_territory, short a_numTroops)
	{
		if(this->isConnectedTo(a_territory))
		{
			if(!(a_numTroops < this->m_troops_deployed))
				a_numTroops = this->m_troops_deployed - ATK_LEAVE_TROOPS;
		
			this->subtractTroopsDeployed(a_numTroops);
			a_territory->addTroopsDeployed(a_numTroops);
		}
	}
	void moveTroopsTo(TemplateArray<Territory *> a_board, short a_ID, short a_numTroops)
	{
		this->moveTroopsTo(a_board.get(a_ID), a_numTroops);
	}
	~Territory(){}
};