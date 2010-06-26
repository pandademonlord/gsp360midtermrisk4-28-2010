//Territory class written by John Parks
#pragma once

#include "circle.h"
#include "triangle.h"
#include "templatearray.h"
#include "random.h"

class Territory
{
private:
	Circle m_area;
	TemplateArray<Triangle *> m_areaTri;
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
	void useContinentColorTri()
	{
		switch(this->m_continentID)
		{
		case CONTINENT_ID_N_AMERICA:
			this->setColorTri(CONTINENT_COLOR_NA);
			break;
		case CONTINENT_ID_S_AMERICA:
			this->setColorTri(CONTINENT_COLOR_SA);
			break;
		case CONTINENT_ID_EUROPE:
			this->setColorTri(CONTINENT_COLOR_EU);
			break;
		case CONTINENT_ID_AFRICA:
			this->setColorTri(CONTINENT_COLOR_AF);
			break;
		case CONTINENT_ID_ASIA:
			this->setColorTri(CONTINENT_COLOR_AS);
			break;
		case CONTINENT_ID_OCEANIA:
			this->setColorTri(CONTINENT_COLOR_OC);
			break;
		}
	
		int r = rand() % 90, g = rand() % 90, b = rand() % 90;
		bool once = false;
		bool onceAgain = false;
		for(int i = 0; i < this->m_areaTri.size(); ++i)
		{		
			//if(this->m_areaTri.get(i)->c_r == 0)
				this->m_areaTri.get(i)->c_r += r;
				this->m_areaTri.get(i)->c_g += g;
			//if(this->m_areaTri.get(i)->c_b == 0)
			if(this->m_continentID == CONTINENT_ID_AFRICA && !once)
			{
				b+=25;
				once = true;
			}
			if(this->m_continentID != CONTINENT_ID_N_AMERICA)
				{this->m_areaTri.get(i)->c_b += b;}
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
	void addTriangle(Triangle * a_tri)
	{
		m_areaTri.add(a_tri);
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
	void setColorTri(short a_r, short a_g, short a_b)
	{
		for(int i = 0; i < this->m_areaTri.size(); ++i)
			this->m_areaTri.get(i)->setColor(a_r, a_g, a_b);
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
	//returns true if this territory is connected to 1+ enemy territories
	bool isConnectedToEnemy()
	{
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_connect.get(i)->getOwner() != this->getOwner())
				return true;
		}
		return false;
	}
	//returns true if this territory is connected to 1+ allied territories
	bool isConnectedToAlly()
	{
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_connect.get(i)->getOwner() == this->getOwner())
				return true;
		}
		return false;
	}
	//check if any enemy connection is surrounded by differently owned territories
	bool connectedToLoneEnemy()
	{
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if((this->m_ownerID != this->m_connect.get(i)->getOwner()) && !(this->m_connect.get(i)->isConnectedToAlly()))
				return true;
		}
		return false;
	}
	//check if any ally connection is surrounded by ally owned territories
	bool connectedToLoneAlly()
	{
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if((this->m_ownerID == this->m_connect.get(i)->getOwner()) && !(this->m_connect.get(i)-isConnectedToEnemy()))
				return true;
		}
		return false;
	}
	//returns a randomly selected Ally-owned connected territory ID
	short getRandAllyTerritoryID()
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_ownerID == this->m_connect.get(i)->getOwner())
				numOfValidOptions++;
		}
		short randAlly = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_ownerID == this->m_connect.get(i)->getOwner())
			{
				if(randAlly == counter)
					return this->m_connect.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//returns a randomly selected Enemy-owned connected territory ID
	short getRandEnemyTerritoryID()
	{
		short numOfValidOptions = 0;
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_ownerID != this->m_connect.get(i)->getOwner())
				numOfValidOptions++;
		}
		short randEnemy = random() % numOfValidOptions;
		short counter = 0;
		for(int i = 0; i < this->m_connect.size(); ++i)
		{
			if(this->m_ownerID != this->m_connect.get(i)->getOwner())
			{
				if(randEnemy == counter)
					return this->m_connect.get(i)->getID();
				else
					counter++;
			}
		}
	}
	//returns true if this territory has at least ATK_FORTIFY_MIN_TROOPS troops
	bool haveTroopsToAttackFority()
	{
		if(this->m_troops_deployed >= ATK_FORTIFY_MIN_TROOPS)
			return true;
		else
			return false;
	}
	//draw the circular clickable area
	void glDraw(){m_area.glDraw();}
	void glDrawWorld()
	{
		for(int i = 0; i < this->m_areaTri.size(); ++i)
			this->m_areaTri.get(i)->glDraw();
	}
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
		//return m_area.isClickable(click);
		for(int i = 0; i < m_areaTri.size(); ++i)
		{
			if(m_areaTri.get(i)->isClickable(click))
				return true;
		}
		return false;
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
	char* getTerName()
	{
		char * terName = new char[20];
		switch(m_ID)
		{
			//North America
			case 0:
				return terName = "Alaska"; 
			case 1:
				return terName = "Alberta"; 
			case 2:
				return terName = "Central America";
			case 3:
				return terName = "Eastern US"; 
			case 4:
				return terName = "Greenland";
			case 5:
				return terName = "Northwest Territory";
			case 6:
				return terName = "Ontario";
			case 7:
				return terName = "Quebec"; 
			case 8:
				return terName = "Western US"; 
			//South America
			case 9:
				return terName = "Argentina";
			case 10:
				return terName = "Brazil"; 
			case 11:
				return terName = "Peru";
			case 12:
				return terName = "Venezuela"; 
			//Europe
			case 13:
				return terName = "Great Britian";
			case 14:
				return terName = "Iceland"; 
			case 15:
				return terName = "Northern Europe"; 
			case 16:
				return terName = "Scandinavia";
			case 17:
				return terName = "Southern Europe"; 
			case 18:
				return terName = "Russia";
			case 19:
				return terName = "Western Europe"; 
			//Africa
			case 20:
				return terName = "Congo"; 
			case 21:
				return terName = "Eastern Africa";
			case 22:
				return terName = "Egypt"; 
			case 23:
				return terName = "Madagascar";
			case 24:
				return terName = "Northern Africa"; 
			case 25:
				return terName = "Southern Africa"; 
			//Asia
			case 26:
				return terName = "Afghanistan"; 
			case 27:
				return terName = "China";
			case 28:
				return terName = "India"; 
			case 29:
				return terName = "Irkutsk"; 
			case 30:
				return terName = "Japan"; 
			case 31:
				return terName = "Kamchatka"; 
			case 32:
				return terName = "Middle East"; 
			case 33:
				return terName = "Mongolia"; 
			case 34:
				return terName = "Siam"; 
			case 35:
				return terName = "Siberia";
			case 36:
				return terName = "Ural";
			case 37:
				return terName = "Yakutsk"; 
			//Oceania
			case 38:
				return terName = "Eastern Australia"; 
			case 39:
				return terName = "Indonesia"; 
			case 40:
				return terName = "New Guinea"; 
			case 41:
				return terName = "Western Australia"; 
			break;
		}
			delete terName;
	}
	~Territory()
	{
		for(int i = 0; i < this->m_areaTri.size(); ++i)
			delete [] this->m_areaTri.get(i);
	}
};