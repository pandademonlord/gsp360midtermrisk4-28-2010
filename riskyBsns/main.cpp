#include <stdio.h>	// for printf()
#include <time.h>	// for clock()

#include <iostream>
using namespace std;

#include "GLUTRenderingContext.h"
#include "random.h"
#include "templatearray.h"
#include "defines.h"
#include "territory.h"
#include "circle.h"
#include "triangle.h"
#include "rect.h"
#include "player.h"
#include "playerai.h"
#include "card.h"


// GLUT will not give access to the main loop, some variables MUST be global. :(
GLUTRenderingContext g_screen(V2DF(SCREEN_WIDTH,SCREEN_HEIGHT), V2DF(SCREEN_MIN_X,SCREEN_MIN_Y), V2DF(SCREEN_MAX_X,SCREEN_MAX_Y));
TemplateArray<Territory *> board;
TemplateArray<Player *> players;
TemplateArray<Card *> deck;
TemplateArray<Rect *> buttons;
short flags[FLAGS_NUM];

void initButtons()
{
	Rect * rec;
	rec = new Rect(V2DF((SCREEN_MIN_X + (8 * SCREEN_HEIGHT/6)), (SCREEN_MIN_Y + SCREEN_HEIGHT/6)), SCREEN_HEIGHT/6, SCREEN_HEIGHT/6);
	buttons.add(rec);
	rec = new Rect(V2DF((SCREEN_MIN_X + (4.25 * SCREEN_HEIGHT/6)), (SCREEN_MIN_Y + (1.75 * SCREEN_HEIGHT/6))), SCREEN_HEIGHT/6, (SCREEN_HEIGHT/6)/2);
	buttons.add(rec);
	rec = new Rect(V2DF((SCREEN_MIN_X + (4.25 * SCREEN_HEIGHT/6)), (SCREEN_MIN_Y + (1 * SCREEN_HEIGHT/6))), SCREEN_HEIGHT/6, (SCREEN_HEIGHT/6)/2);
	buttons.add(rec);

	for(int i = 0; i < buttons.size(); ++i)
		buttons.get(i)->setColor(HIGHLIGHT_COLOR);
}
void initBoard()
{
	initButtons();

	Territory * ter;

	//set continent ID
	for(int i = TERRITORIES_ST_N_AMERICA; i < TERRITORIES_ST_S_AMERICA; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_N_AMERICA);
		board.add(ter);
	}
	for(int i = TERRITORIES_ST_S_AMERICA; i < TERRITORIES_ST_EUROPE; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_S_AMERICA);
		board.add(ter);
	}
	for(int i = TERRITORIES_ST_EUROPE; i < TERRITORIES_ST_AFRICA; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_EUROPE);
		board.add(ter);
	}
	for(int i = TERRITORIES_ST_AFRICA; i < TERRITORIES_ST_ASIA; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_AFRICA);
		board.add(ter);
	}
	for(int i = TERRITORIES_ST_ASIA; i < TERRITORIES_ST_OCEANIA; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_ASIA);
		board.add(ter);
	}
	for(int i = TERRITORIES_ST_OCEANIA; i < TERRITORIES_TOTAL; ++i)
	{
		ter = new Territory(board.size(), CONTINENT_ID_OCEANIA);
		board.add(ter);
	}

	Triangle * tri;

	//North America
		//1. Alaska
	
	board.get(ID_ALASKA)->setArea(g_screen.convertPixelsToCartesian(V2DF(90,72)),22);
	board.get(ID_ALASKA)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_ALASKA)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ALASKA)->addConnection(board.get(ID_KAMCHATKA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(9,114)),
						g_screen.convertPixelsToCartesian(V2DF(76,90)),
						g_screen.convertPixelsToCartesian(V2DF(53,75)));
	board.get(ID_ALASKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(96,92)),
						g_screen.convertPixelsToCartesian(V2DF(140,57)),
						g_screen.convertPixelsToCartesian(V2DF(92,53)));
	board.get(ID_ALASKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(76,90)),
						g_screen.convertPixelsToCartesian(V2DF(96,92)),
						g_screen.convertPixelsToCartesian(V2DF(92,53)));
	board.get(ID_ALASKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(76,90)),
						g_screen.convertPixelsToCartesian(V2DF(92,53)),
						g_screen.convertPixelsToCartesian(V2DF(53,75)));
	board.get(ID_ALASKA)->addTriangle(tri);
		//2. Alberta
	board.get(ID_ALBERTA)->setArea(g_screen.convertPixelsToCartesian(V2DF(159,118)),22);
	board.get(ID_ALBERTA)->addConnection(board.get(ID_ALASKA));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_W_US));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(113,140)),
						g_screen.convertPixelsToCartesian(V2DF(190,143)),
						g_screen.convertPixelsToCartesian(V2DF(113,144)));
	board.get(ID_ALBERTA)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(190,141)),
						g_screen.convertPixelsToCartesian(V2DF(219,96)),
						g_screen.convertPixelsToCartesian(V2DF(101,95)));
	board.get(ID_ALBERTA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(113,141)),
						g_screen.convertPixelsToCartesian(V2DF(190,141)),
						g_screen.convertPixelsToCartesian(V2DF(113,101)));
	board.get(ID_ALBERTA)->addTriangle(tri);
		//3. Central America
	board.get(ID_C_AMERICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(143,263)),22);
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_E_US));
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_W_US));
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_VENEZUELA));
	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(91,216)),
						g_screen.convertPixelsToCartesian(V2DF(145,219)),
						g_screen.convertPixelsToCartesian(V2DF(139,237)));
	board.get(ID_C_AMERICA)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(92,217)),
						g_screen.convertPixelsToCartesian(V2DF(107,260)),
						g_screen.convertPixelsToCartesian(V2DF(102,216)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(102,216)),
						g_screen.convertPixelsToCartesian(V2DF(154,304)),
						g_screen.convertPixelsToCartesian(V2DF(134,220)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(134,220)),
						g_screen.convertPixelsToCartesian(V2DF(154,304)),
						g_screen.convertPixelsToCartesian(V2DF(162,246)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(129,260)),
						g_screen.convertPixelsToCartesian(V2DF(124,277)),
						g_screen.convertPixelsToCartesian(V2DF(144,286)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(155,293)),
						g_screen.convertPixelsToCartesian(V2DF(234,327)),
						g_screen.convertPixelsToCartesian(V2DF(157,275)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(170,284)),
						g_screen.convertPixelsToCartesian(V2DF(187,295)),
						g_screen.convertPixelsToCartesian(V2DF(199,268)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(187,295)),
						g_screen.convertPixelsToCartesian(V2DF(208,310)),
						g_screen.convertPixelsToCartesian(V2DF(211,293)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(216,261)),
						g_screen.convertPixelsToCartesian(V2DF(236,272)),
						g_screen.convertPixelsToCartesian(V2DF(240,262)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(240,262)),
						g_screen.convertPixelsToCartesian(V2DF(236,272)),
						g_screen.convertPixelsToCartesian(V2DF(240,262)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(255,280)),
						g_screen.convertPixelsToCartesian(V2DF(265,282)),
						g_screen.convertPixelsToCartesian(V2DF(265,275)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(265,275)),
						g_screen.convertPixelsToCartesian(V2DF(265,282)),
						g_screen.convertPixelsToCartesian(V2DF(273,278)));
	board.get(ID_C_AMERICA)->addTriangle(tri);
		//4. Eastern United States
	board.get(ID_E_US)->setArea(g_screen.convertPixelsToCartesian(V2DF(220,200)),22);
	board.get(ID_E_US)->addConnection(board.get(ID_C_AMERICA));
	board.get(ID_E_US)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_E_US)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_E_US)->addConnection(board.get(ID_W_US));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(142,228)),
						g_screen.convertPixelsToCartesian(V2DF(162,246)),
						g_screen.convertPixelsToCartesian(V2DF(152,198)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(161,240)),
						g_screen.convertPixelsToCartesian(V2DF(183,226)),
						g_screen.convertPixelsToCartesian(V2DF(157,224)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(152,198)),
						g_screen.convertPixelsToCartesian(V2DF(157,224)),
						g_screen.convertPixelsToCartesian(V2DF(222,230)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(152,198)),
						g_screen.convertPixelsToCartesian(V2DF(222,230)),
						g_screen.convertPixelsToCartesian(V2DF(215,198)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(222,226)),
						g_screen.convertPixelsToCartesian(V2DF(228,249)),
						g_screen.convertPixelsToCartesian(V2DF(234,219)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(215,198)),
						g_screen.convertPixelsToCartesian(V2DF(222,226)),
						g_screen.convertPixelsToCartesian(V2DF(260,200)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(198,144)),
						g_screen.convertPixelsToCartesian(V2DF(190,199)),
						g_screen.convertPixelsToCartesian(V2DF(260,199))); //fixed
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(198,144)),
						g_screen.convertPixelsToCartesian(V2DF(258,198)),
						g_screen.convertPixelsToCartesian(V2DF(284,176)));
	board.get(ID_E_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(263,168)),
						g_screen.convertPixelsToCartesian(V2DF(284,176)),
						g_screen.convertPixelsToCartesian(V2DF(309,152)));
	board.get(ID_E_US)->addTriangle(tri);
		//5. Greenland
	board.get(ID_GREENLAND)->setArea(g_screen.convertPixelsToCartesian(V2DF(453,42)),22);
	board.get(ID_GREENLAND)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_ICELAND));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(378,26)),
						g_screen.convertPixelsToCartesian(V2DF(401,32)),
						g_screen.convertPixelsToCartesian(V2DF(424,15)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(424,15)),
						g_screen.convertPixelsToCartesian(V2DF(401,32)),
						g_screen.convertPixelsToCartesian(V2DF(416,55)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(424,15)),
						g_screen.convertPixelsToCartesian(V2DF(416,55)),
						g_screen.convertPixelsToCartesian(V2DF(492,44)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(424,15)),
						g_screen.convertPixelsToCartesian(V2DF(492,44)),
						g_screen.convertPixelsToCartesian(V2DF(534,16)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(416,55)),
						g_screen.convertPixelsToCartesian(V2DF(496,58)),
						g_screen.convertPixelsToCartesian(V2DF(492,44)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(416,55)),
						g_screen.convertPixelsToCartesian(V2DF(401,83)),
						g_screen.convertPixelsToCartesian(V2DF(419,94)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(416,55)),
						g_screen.convertPixelsToCartesian(V2DF(419,94)),
						g_screen.convertPixelsToCartesian(V2DF(436,75)));
	board.get(ID_GREENLAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(416,55)),
						g_screen.convertPixelsToCartesian(V2DF(436,75)),
						g_screen.convertPixelsToCartesian(V2DF(496,58)));
	board.get(ID_GREENLAND)->addTriangle(tri);
		//6. Northwest Territory
	board.get(ID_NW_TERRITORY)->setArea(g_screen.convertPixelsToCartesian(V2DF(182,73)),22);
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ALASKA));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ONTARIO));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(140,57)),
						g_screen.convertPixelsToCartesian(V2DF(93,95)),
						g_screen.convertPixelsToCartesian(V2DF(245,95)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(140,57)),
						g_screen.convertPixelsToCartesian(V2DF(245,95)),
						g_screen.convertPixelsToCartesian(V2DF(202,58)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(202,58)),
						g_screen.convertPixelsToCartesian(V2DF(245,95)),
						g_screen.convertPixelsToCartesian(V2DF(234,70)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(234,70)),
						g_screen.convertPixelsToCartesian(V2DF(245,95)),
						g_screen.convertPixelsToCartesian(V2DF(245,62)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(245,62)),
						g_screen.convertPixelsToCartesian(V2DF(245,95)),
						g_screen.convertPixelsToCartesian(V2DF(291,74)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(270,68)),
						g_screen.convertPixelsToCartesian(V2DF(291,74)),
						g_screen.convertPixelsToCartesian(V2DF(292,49)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(292,53)),
						g_screen.convertPixelsToCartesian(V2DF(291,74)),
						g_screen.convertPixelsToCartesian(V2DF(318,60)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(292,45)),
						g_screen.convertPixelsToCartesian(V2DF(305,43)),
						g_screen.convertPixelsToCartesian(V2DF(298,40)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(278,42)),
						g_screen.convertPixelsToCartesian(V2DF(277,51)), //fixed
						g_screen.convertPixelsToCartesian(V2DF(289,42)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(223,39)),
						g_screen.convertPixelsToCartesian(V2DF(203,49)),
						g_screen.convertPixelsToCartesian(V2DF(221,46)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(223,39)),
						g_screen.convertPixelsToCartesian(V2DF(217,60)),
						g_screen.convertPixelsToCartesian(V2DF(264,55)));
	board.get(ID_NW_TERRITORY)->addTriangle(tri);
		//7. Ontario
	board.get(ID_ONTARIO)->setArea(g_screen.convertPixelsToCartesian(V2DF(239,124)),22);
	board.get(ID_ONTARIO)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_E_US));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_W_US));

	//new fix
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(266,152)),
						g_screen.convertPixelsToCartesian(V2DF(264,169)),
						g_screen.convertPixelsToCartesian(V2DF(289,158)));
	board.get(ID_ONTARIO)->addTriangle(tri);
	//new fix
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(192,140)),
						g_screen.convertPixelsToCartesian(V2DF(264,169)),
						g_screen.convertPixelsToCartesian(V2DF(266,152)));
	board.get(ID_ONTARIO)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(193,141)),
						g_screen.convertPixelsToCartesian(V2DF(264,141)),
						g_screen.convertPixelsToCartesian(V2DF(266,152)));
	board.get(ID_ONTARIO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(266,152)),
						g_screen.convertPixelsToCartesian(V2DF(264,141)),
						g_screen.convertPixelsToCartesian(V2DF(291,157)));
	board.get(ID_ONTARIO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(193,141)),
						g_screen.convertPixelsToCartesian(V2DF(266,152)),
						g_screen.convertPixelsToCartesian(V2DF(273,117)));
	board.get(ID_ONTARIO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(245,96)),
						g_screen.convertPixelsToCartesian(V2DF(193,141)),
						g_screen.convertPixelsToCartesian(V2DF(273,117)));
	board.get(ID_ONTARIO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(220,96)),
						g_screen.convertPixelsToCartesian(V2DF(193,141)),
						g_screen.convertPixelsToCartesian(V2DF(245,96)));
	board.get(ID_ONTARIO)->addTriangle(tri);
		//8. Quebec
	board.get(ID_QUEBEC)->setArea(g_screen.convertPixelsToCartesian(V2DF(320,120)),22);
	board.get(ID_QUEBEC)->addConnection(board.get(ID_E_US));
	board.get(ID_QUEBEC)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_QUEBEC)->addConnection(board.get(ID_ONTARIO));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(266,152)),
						g_screen.convertPixelsToCartesian(V2DF(291,157)),
						g_screen.convertPixelsToCartesian(V2DF(275,134)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(275,134)),
						g_screen.convertPixelsToCartesian(V2DF(291,157)),
						g_screen.convertPixelsToCartesian(V2DF(302,110)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,110)),
						g_screen.convertPixelsToCartesian(V2DF(291,157)),
						g_screen.convertPixelsToCartesian(V2DF(311,142)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,110)),
						g_screen.convertPixelsToCartesian(V2DF(311,142)),
						g_screen.convertPixelsToCartesian(V2DF(355,134)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,110)),
						g_screen.convertPixelsToCartesian(V2DF(355,134)),
						g_screen.convertPixelsToCartesian(V2DF(350,123)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,110)),
						g_screen.convertPixelsToCartesian(V2DF(350,123)),
						g_screen.convertPixelsToCartesian(V2DF(335,105)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,100)),
						g_screen.convertPixelsToCartesian(V2DF(302,110)),
						g_screen.convertPixelsToCartesian(V2DF(335,105)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,100)),
						g_screen.convertPixelsToCartesian(V2DF(335,105)),
						g_screen.convertPixelsToCartesian(V2DF(317,85)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(335,105)),
						g_screen.convertPixelsToCartesian(V2DF(350,123)),
						g_screen.convertPixelsToCartesian(V2DF(350,96)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(350,123)),
						g_screen.convertPixelsToCartesian(V2DF(335,134)),
						g_screen.convertPixelsToCartesian(V2DF(364,122)));
	board.get(ID_QUEBEC)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(311,142)),
						g_screen.convertPixelsToCartesian(V2DF(313,165)),
						g_screen.convertPixelsToCartesian(V2DF(338,155)));
	board.get(ID_QUEBEC)->addTriangle(tri);
		//9. Western United States
	board.get(ID_W_US)->setArea(g_screen.convertPixelsToCartesian(V2DF(125,174)),22);
	board.get(ID_W_US)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_W_US)->addConnection(board.get(ID_C_AMERICA));
	board.get(ID_W_US)->addConnection(board.get(ID_E_US));
	board.get(ID_W_US)->addConnection(board.get(ID_ONTARIO));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(197,144)),
						g_screen.convertPixelsToCartesian(V2DF(116,144)),
						g_screen.convertPixelsToCartesian(V2DF(190,199)));
	board.get(ID_W_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(116,144)),
						g_screen.convertPixelsToCartesian(V2DF(152,199)),
						g_screen.convertPixelsToCartesian(V2DF(190,199)));
	board.get(ID_W_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(115,144)),
						g_screen.convertPixelsToCartesian(V2DF(145,217)),
						g_screen.convertPixelsToCartesian(V2DF(152,199)));
	board.get(ID_W_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(116,144)),
						g_screen.convertPixelsToCartesian(V2DF(92,215)),
						g_screen.convertPixelsToCartesian(V2DF(147,217)));
	board.get(ID_W_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(116,144)),
						g_screen.convertPixelsToCartesian(V2DF(82,181)),
						g_screen.convertPixelsToCartesian(V2DF(101,188)));
	board.get(ID_W_US)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(82,181)),
						g_screen.convertPixelsToCartesian(V2DF(93,214)),
						g_screen.convertPixelsToCartesian(V2DF(101,188)));
	board.get(ID_W_US)->addTriangle(tri);

	//South America
		//1. Argentina
	board.get(ID_ARGENTINA)->setArea(g_screen.convertPixelsToCartesian(V2DF(301,521)),22);
	board.get(ID_ARGENTINA)->addConnection(board.get(ID_PERU));
	board.get(ID_ARGENTINA)->addConnection(board.get(ID_BRAZIL));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(267,449)),
						g_screen.convertPixelsToCartesian(V2DF(277,552)),
						g_screen.convertPixelsToCartesian(V2DF(314,548)));
	board.get(ID_ARGENTINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(267,449)),
						g_screen.convertPixelsToCartesian(V2DF(314,548)),
						g_screen.convertPixelsToCartesian(V2DF(349,513)));
	board.get(ID_ARGENTINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(267,449)),
						g_screen.convertPixelsToCartesian(V2DF(328,497)),
						g_screen.convertPixelsToCartesian(V2DF(340,483)));
	board.get(ID_ARGENTINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(277,552)),
						g_screen.convertPixelsToCartesian(V2DF(309,604)),
						g_screen.convertPixelsToCartesian(V2DF(314,548)));
	board.get(ID_ARGENTINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(317,602)),
						g_screen.convertPixelsToCartesian(V2DF(313,608)),
						g_screen.convertPixelsToCartesian(V2DF(335,614)));
	board.get(ID_ARGENTINA)->addTriangle(tri);
		//2. Brazil
	board.get(ID_BRAZIL)->setArea(g_screen.convertPixelsToCartesian(V2DF(346,412)),22);
	board.get(ID_BRAZIL)->addConnection(board.get(ID_ARGENTINA));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_PERU));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_VENEZUELA));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_N_AFRICA));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(316,436)),
						g_screen.convertPixelsToCartesian(V2DF(321,369)),
						g_screen.convertPixelsToCartesian(V2DF(344,488)));
	board.get(ID_BRAZIL)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(268,359)),
						g_screen.convertPixelsToCartesian(V2DF(250,399)),
						g_screen.convertPixelsToCartesian(V2DF(293,402)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(250,399)),
						g_screen.convertPixelsToCartesian(V2DF(268,415)),
						g_screen.convertPixelsToCartesian(V2DF(293,402)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(268,359)),
						g_screen.convertPixelsToCartesian(V2DF(315,438)),
						g_screen.convertPixelsToCartesian(V2DF(338,357)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(293,402)),
						g_screen.convertPixelsToCartesian(V2DF(281,408)),
						g_screen.convertPixelsToCartesian(V2DF(315,437)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(341,348)),
						g_screen.convertPixelsToCartesian(V2DF(315,347)),
						g_screen.convertPixelsToCartesian(V2DF(411,395)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(411,395)),
						g_screen.convertPixelsToCartesian(V2DF(315,347)),
						g_screen.convertPixelsToCartesian(V2DF(342,484)));
	board.get(ID_BRAZIL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(411,395)),
						g_screen.convertPixelsToCartesian(V2DF(329,500)),
						g_screen.convertPixelsToCartesian(V2DF(350,515)));
	board.get(ID_BRAZIL)->addTriangle(tri);
		//3. Peru
	board.get(ID_PERU)->setArea(g_screen.convertPixelsToCartesian(V2DF(266,425)),22);
	board.get(ID_PERU)->addConnection(board.get(ID_ARGENTINA));
	board.get(ID_PERU)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_PERU)->addConnection(board.get(ID_VENEZUELA));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(281,410)),
						g_screen.convertPixelsToCartesian(V2DF(342,486)),
						g_screen.convertPixelsToCartesian(V2DF(316,437)));
	board.get(ID_PERU)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(227,357)),
						g_screen.convertPixelsToCartesian(V2DF(217,387)),
						g_screen.convertPixelsToCartesian(V2DF(257,383)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(217,387)),
						g_screen.convertPixelsToCartesian(V2DF(244,421)),
						g_screen.convertPixelsToCartesian(V2DF(257,383)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(251,399)),
						g_screen.convertPixelsToCartesian(V2DF(244,421)),
						g_screen.convertPixelsToCartesian(V2DF(268,415)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(244,421)),
						g_screen.convertPixelsToCartesian(V2DF(266,447)),
						g_screen.convertPixelsToCartesian(V2DF(281,409)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(281,409)),
						g_screen.convertPixelsToCartesian(V2DF(266,447)),
						g_screen.convertPixelsToCartesian(V2DF(299,464)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(281,409)),
						g_screen.convertPixelsToCartesian(V2DF(299,464)),
						g_screen.convertPixelsToCartesian(V2DF(325,478)));
	board.get(ID_PERU)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(281,409)),
						g_screen.convertPixelsToCartesian(V2DF(325,478)),
						g_screen.convertPixelsToCartesian(V2DF(336,477)));
	board.get(ID_PERU)->addTriangle(tri);
		//4. Venezuela
	board.get(ID_VENEZUELA)->setArea(g_screen.convertPixelsToCartesian(V2DF(263,335)),22);
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_PERU));
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_C_AMERICA));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(240,358)),
						g_screen.convertPixelsToCartesian(V2DF(309,337)), 
						g_screen.convertPixelsToCartesian(V2DF(309,358)));
	board.get(ID_VENEZUELA)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(245,315)),
						g_screen.convertPixelsToCartesian(V2DF(227,358)), //fixed
						g_screen.convertPixelsToCartesian(V2DF(266,355)));
	board.get(ID_VENEZUELA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(227,358)), //fixed
						g_screen.convertPixelsToCartesian(V2DF(264,383)),
						g_screen.convertPixelsToCartesian(V2DF(266,355)));
	board.get(ID_VENEZUELA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(245,315)),
						g_screen.convertPixelsToCartesian(V2DF(266,355)),
						g_screen.convertPixelsToCartesian(V2DF(258,309)));
	board.get(ID_VENEZUELA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(258,309)),
						g_screen.convertPixelsToCartesian(V2DF(266,355)),
						g_screen.convertPixelsToCartesian(V2DF(302,341)));
	board.get(ID_VENEZUELA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(258,309)),
						g_screen.convertPixelsToCartesian(V2DF(302,341)),
						g_screen.convertPixelsToCartesian(V2DF(340,347)));
	board.get(ID_VENEZUELA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(302,341)),
						g_screen.convertPixelsToCartesian(V2DF(307,358)),
						g_screen.convertPixelsToCartesian(V2DF(340,347)));
	board.get(ID_VENEZUELA)->addTriangle(tri);

	//Europe
		//1. Great Britain
	board.get(ID_GREAT_BRITIAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(556,125)),22);
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_ICELAND));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_W_EUROPE));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(546,98)),
						g_screen.convertPixelsToCartesian(V2DF(542,138)),
						g_screen.convertPixelsToCartesian(V2DF(568,134)));
	board.get(ID_GREAT_BRITIAN)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(544,116)),
						g_screen.convertPixelsToCartesian(V2DF(530,116)),
						g_screen.convertPixelsToCartesian(V2DF(539,131)));
	board.get(ID_GREAT_BRITIAN)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(530,116)),
						g_screen.convertPixelsToCartesian(V2DF(522,135)),
						g_screen.convertPixelsToCartesian(V2DF(539,131)));
	board.get(ID_GREAT_BRITIAN)->addTriangle(tri);
		//2. Iceland
	board.get(ID_ICELAND)->setArea(g_screen.convertPixelsToCartesian(V2DF(508,75)),22);
	board.get(ID_ICELAND)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_ICELAND)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_ICELAND)->addConnection(board.get(ID_SCANDINAVIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(517,63)),
						g_screen.convertPixelsToCartesian(V2DF(486,76)),
						g_screen.convertPixelsToCartesian(V2DF(525,76)));
	board.get(ID_ICELAND)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(486,76)),
						g_screen.convertPixelsToCartesian(V2DF(501,87)),
						g_screen.convertPixelsToCartesian(V2DF(525,76)));
	board.get(ID_ICELAND)->addTriangle(tri);
		//3. Northern Europe
	board.get(ID_N_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(610,131)),22);
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_W_EUROPE));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(638,114)),
						g_screen.convertPixelsToCartesian(V2DF(623,152)),
						g_screen.convertPixelsToCartesian(V2DF(652,136)));
	board.get(ID_N_EUROPE)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(597,106)),
						g_screen.convertPixelsToCartesian(V2DF(571,135)),
						g_screen.convertPixelsToCartesian(V2DF(587,147)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(597,106)),
						g_screen.convertPixelsToCartesian(V2DF(587,147)),
						g_screen.convertPixelsToCartesian(V2DF(601,121)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(601,121)),
						g_screen.convertPixelsToCartesian(V2DF(587,147)),
						g_screen.convertPixelsToCartesian(V2DF(626,145)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(601,121)),
						g_screen.convertPixelsToCartesian(V2DF(626,145)),
						g_screen.convertPixelsToCartesian(V2DF(638,115)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(638,155)), //fixed
						g_screen.convertPixelsToCartesian(V2DF(621,152)),
						g_screen.convertPixelsToCartesian(V2DF(650,137)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(650,137)),
						g_screen.convertPixelsToCartesian(V2DF(621,152)),
						g_screen.convertPixelsToCartesian(V2DF(639,155)));
	board.get(ID_N_EUROPE)->addTriangle(tri);
		//4. Scandinavia
	board.get(ID_SCANDINAVIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(625,68)),22);
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_ICELAND));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_GREAT_BRITIAN));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(632,51)),
						g_screen.convertPixelsToCartesian(V2DF(578,92)),
						g_screen.convertPixelsToCartesian(V2DF(632,94)));
	board.get(ID_SCANDINAVIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(632,51)),
						g_screen.convertPixelsToCartesian(V2DF(632,94)),
						g_screen.convertPixelsToCartesian(V2DF(655,53)));
	board.get(ID_SCANDINAVIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(655,53)),
						g_screen.convertPixelsToCartesian(V2DF(632,94)),
						g_screen.convertPixelsToCartesian(V2DF(660,92)));
	board.get(ID_SCANDINAVIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(578,92)),
						g_screen.convertPixelsToCartesian(V2DF(612,114)),
						g_screen.convertPixelsToCartesian(V2DF(632,94)));
	board.get(ID_SCANDINAVIA)->addTriangle(tri);
		//5. Southern Europe
	board.get(ID_S_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(643,166)),22);
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_EGYPT));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_W_EUROPE));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(625,146)),
						g_screen.convertPixelsToCartesian(V2DF(586,147)),
						g_screen.convertPixelsToCartesian(V2DF(622,153)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(586,147)),
						g_screen.convertPixelsToCartesian(V2DF(587,167)),
						g_screen.convertPixelsToCartesian(V2DF(640,155)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(640,155)),
						g_screen.convertPixelsToCartesian(V2DF(587,167)),
						g_screen.convertPixelsToCartesian(V2DF(622,191)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(640,155)),
						g_screen.convertPixelsToCartesian(V2DF(622,191)),
						g_screen.convertPixelsToCartesian(V2DF(648,199)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(640,155)),
						g_screen.convertPixelsToCartesian(V2DF(648,199)),
						g_screen.convertPixelsToCartesian(V2DF(670,161)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(640,155)),
						g_screen.convertPixelsToCartesian(V2DF(670,161)),
						g_screen.convertPixelsToCartesian(V2DF(660,147)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(644,147)),
						g_screen.convertPixelsToCartesian(V2DF(640,155)),
						g_screen.convertPixelsToCartesian(V2DF(660,147)));
	board.get(ID_S_EUROPE)->addTriangle(tri);
		//6. Russia
	board.get(ID_RUSSIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(706,110)),22);
	board.get(ID_RUSSIA)->addConnection(board.get(ID_URAL));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_S_EUROPE));
	
	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(749,81)),
						g_screen.convertPixelsToCartesian(V2DF(744,131)),
						g_screen.convertPixelsToCartesian(V2DF(784,136)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(782,120)),
						g_screen.convertPixelsToCartesian(V2DF(774,120)),
						g_screen.convertPixelsToCartesian(V2DF(782,132)));
	board.get(ID_RUSSIA)->addTriangle(tri);


	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(655,54)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)),
						g_screen.convertPixelsToCartesian(V2DF(759,57)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(759,57)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)),
						g_screen.convertPixelsToCartesian(V2DF(767,67)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(655,54)),
						g_screen.convertPixelsToCartesian(V2DF(660,93)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(660,93)),
						g_screen.convertPixelsToCartesian(V2DF(636,111)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(636,111)),
						g_screen.convertPixelsToCartesian(V2DF(669,159)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(669,159)),
						g_screen.convertPixelsToCartesian(V2DF(702,162)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(702,162)),
						g_screen.convertPixelsToCartesian(V2DF(746,130)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(746,130)),
						g_screen.convertPixelsToCartesian(V2DF(738,135)),
						g_screen.convertPixelsToCartesian(V2DF(747,80)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(702,162)),
						g_screen.convertPixelsToCartesian(V2DF(716,176)),
						g_screen.convertPixelsToCartesian(V2DF(728,142)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(728,142)),
						g_screen.convertPixelsToCartesian(V2DF(716,176)),
						g_screen.convertPixelsToCartesian(V2DF(743,154)));
	board.get(ID_RUSSIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(743,154)),
						g_screen.convertPixelsToCartesian(V2DF(716,176)),
						g_screen.convertPixelsToCartesian(V2DF(749,190)));
	board.get(ID_RUSSIA)->addTriangle(tri);
		//7. Western Europe
	board.get(ID_W_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(544,182)),22);
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_S_EUROPE));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(585,147)),
						g_screen.convertPixelsToCartesian(V2DF(571,135)),
						g_screen.convertPixelsToCartesian(V2DF(544,145)));
	board.get(ID_W_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(585,147)),
						g_screen.convertPixelsToCartesian(V2DF(544,145)),
						g_screen.convertPixelsToCartesian(V2DF(525,167)));
	board.get(ID_W_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(585,147)),
						g_screen.convertPixelsToCartesian(V2DF(525,167)),
						g_screen.convertPixelsToCartesian(V2DF(522,197)));
	board.get(ID_W_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(585,147)),
						g_screen.convertPixelsToCartesian(V2DF(522,197)),
						g_screen.convertPixelsToCartesian(V2DF(548,198)));
	board.get(ID_W_EUROPE)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(585,147)),
						g_screen.convertPixelsToCartesian(V2DF(548,198)),
						g_screen.convertPixelsToCartesian(V2DF(587,167)));
	board.get(ID_W_EUROPE)->addTriangle(tri);

	//Africa
		//1. Congo
	board.get(ID_CONGO)->setArea(g_screen.convertPixelsToCartesian(V2DF(650,367)),22);
	board.get(ID_CONGO)->addConnection(board.get(ID_S_AFRICA));
	board.get(ID_CONGO)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_CONGO)->addConnection(board.get(ID_E_AFRICA));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(652,317)),
						g_screen.convertPixelsToCartesian(V2DF(669,345)),
						g_screen.convertPixelsToCartesian(V2DF(677,346)));
	board.get(ID_CONGO)->addTriangle(tri);
	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(702,353)),
						g_screen.convertPixelsToCartesian(V2DF(681,376)),
						g_screen.convertPixelsToCartesian(V2DF(675,404)));
	board.get(ID_CONGO)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(596,354)),
						g_screen.convertPixelsToCartesian(V2DF(607,391)),
						g_screen.convertPixelsToCartesian(V2DF(643,396)));
	board.get(ID_CONGO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(596,354)),
						g_screen.convertPixelsToCartesian(V2DF(643,396)),
						g_screen.convertPixelsToCartesian(V2DF(624,354)));
	board.get(ID_CONGO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(616,337)),
						g_screen.convertPixelsToCartesian(V2DF(651,414)),
						g_screen.convertPixelsToCartesian(V2DF(651,316)));
	board.get(ID_CONGO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(651,316)),
						g_screen.convertPixelsToCartesian(V2DF(651,414)),
						g_screen.convertPixelsToCartesian(V2DF(686,370)));
	board.get(ID_CONGO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(670,344)),
						g_screen.convertPixelsToCartesian(V2DF(686,370)),
						g_screen.convertPixelsToCartesian(V2DF(700,352)));
	board.get(ID_CONGO)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(686,370)),
						g_screen.convertPixelsToCartesian(V2DF(651,414)),
						g_screen.convertPixelsToCartesian(V2DF(672,420)));
	board.get(ID_CONGO)->addTriangle(tri);
		//2. East Africa
	board.get(ID_E_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(707,322)),22);
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_EGYPT));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_MADAGASCAR));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_CONGO));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_S_AFRICA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(658,266)),
						g_screen.convertPixelsToCartesian(V2DF(654,319)),
						g_screen.convertPixelsToCartesian(V2DF(706,265))); //fixed
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(706,265)),
						g_screen.convertPixelsToCartesian(V2DF(654,319)),
						g_screen.convertPixelsToCartesian(V2DF(741,319)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(741,319)),
						g_screen.convertPixelsToCartesian(V2DF(654,319)),
						g_screen.convertPixelsToCartesian(V2DF(677,345)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(774,305)),
						g_screen.convertPixelsToCartesian(V2DF(677,345)),
						g_screen.convertPixelsToCartesian(V2DF(741,362)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(703,352)),
						g_screen.convertPixelsToCartesian(V2DF(681,400)),
						g_screen.convertPixelsToCartesian(V2DF(725,415)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(692,404)),
						g_screen.convertPixelsToCartesian(V2DF(698,441)),
						g_screen.convertPixelsToCartesian(V2DF(725,415)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(703,352)),
						g_screen.convertPixelsToCartesian(V2DF(725,415)),
						g_screen.convertPixelsToCartesian(V2DF(739,363)));
	board.get(ID_E_AFRICA)->addTriangle(tri);
		//3. Egypt
	board.get(ID_EGYPT)->setArea(g_screen.convertPixelsToCartesian(V2DF(648,242)),22);
	board.get(ID_EGYPT)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_EGYPT)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_EGYPT)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_EGYPT)->addConnection(board.get(ID_N_AFRICA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(604,214)),
						g_screen.convertPixelsToCartesian(V2DF(594,247)),
						g_screen.convertPixelsToCartesian(V2DF(616,261)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(604,214)),
						g_screen.convertPixelsToCartesian(V2DF(616,261)),
						g_screen.convertPixelsToCartesian(V2DF(634,227)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(634,227)),
						g_screen.convertPixelsToCartesian(V2DF(616,261)),
						g_screen.convertPixelsToCartesian(V2DF(655,276)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(634,227)),
						g_screen.convertPixelsToCartesian(V2DF(655,276)),
						g_screen.convertPixelsToCartesian(V2DF(669,226)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(642,215)),
						g_screen.convertPixelsToCartesian(V2DF(636,227)),
						g_screen.convertPixelsToCartesian(V2DF(692,226)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(669,226)),
						g_screen.convertPixelsToCartesian(V2DF(658,264)),
						g_screen.convertPixelsToCartesian(V2DF(703,264)));
	board.get(ID_EGYPT)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(669,226)),
						g_screen.convertPixelsToCartesian(V2DF(703,264)),
						g_screen.convertPixelsToCartesian(V2DF(695,226)));
	board.get(ID_EGYPT)->addTriangle(tri);
		//4. Madagascar
	board.get(ID_MADAGASCAR)->setArea(g_screen.convertPixelsToCartesian(V2DF(749,451)),22);
	board.get(ID_MADAGASCAR)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_MADAGASCAR)->addConnection(board.get(ID_S_AFRICA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(762,421)),
						g_screen.convertPixelsToCartesian(V2DF(741,440)),
						g_screen.convertPixelsToCartesian(V2DF(761,442)));
	board.get(ID_MADAGASCAR)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(761,442)),
						g_screen.convertPixelsToCartesian(V2DF(741,440)),
						g_screen.convertPixelsToCartesian(V2DF(746,482)));
	board.get(ID_MADAGASCAR)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(741,440)),
						g_screen.convertPixelsToCartesian(V2DF(735,477)),
						g_screen.convertPixelsToCartesian(V2DF(746,482)));
	board.get(ID_MADAGASCAR)->addTriangle(tri);
		//5. North Africa
	board.get(ID_N_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(561,279)),22);
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_W_EUROPE));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_EGYPT));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_CONGO));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(655,275)),
						g_screen.convertPixelsToCartesian(V2DF(616,336)),
						g_screen.convertPixelsToCartesian(V2DF(653,315)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(618,258)),
						g_screen.convertPixelsToCartesian(V2DF(616,336)),
						g_screen.convertPixelsToCartesian(V2DF(655,275)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(593,248)),
						g_screen.convertPixelsToCartesian(V2DF(616,336)),
						g_screen.convertPixelsToCartesian(V2DF(618,264)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(593,248)),
						g_screen.convertPixelsToCartesian(V2DF(599,352)),
						g_screen.convertPixelsToCartesian(V2DF(616,336)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(593,248)),
						g_screen.convertPixelsToCartesian(V2DF(569,333)),
						g_screen.convertPixelsToCartesian(V2DF(599,352)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(616,336)),
						g_screen.convertPixelsToCartesian(V2DF(597,354)),
						g_screen.convertPixelsToCartesian(V2DF(624,354)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(598,196)),
						g_screen.convertPixelsToCartesian(V2DF(536,202)),
						g_screen.convertPixelsToCartesian(V2DF(604,215)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(536,202)),
						g_screen.convertPixelsToCartesian(V2DF(569,333)),
						g_screen.convertPixelsToCartesian(V2DF(604,215)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(536,202)),
						g_screen.convertPixelsToCartesian(V2DF(523,345)),
						g_screen.convertPixelsToCartesian(V2DF(569,333)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(536,202)),
						g_screen.convertPixelsToCartesian(V2DF(480,299)),
						g_screen.convertPixelsToCartesian(V2DF(523,345)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(536,202)),
						g_screen.convertPixelsToCartesian(V2DF(511,223)),
						g_screen.convertPixelsToCartesian(V2DF(480,299)));
	board.get(ID_N_AFRICA)->addTriangle(tri);
		//6. South Africa
	board.get(ID_S_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(658,457)),22);
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_CONGO));
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_MADAGASCAR));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(724,415)),
						g_screen.convertPixelsToCartesian(V2DF(698,440)),
						g_screen.convertPixelsToCartesian(V2DF(724,434)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(698,440)),
						g_screen.convertPixelsToCartesian(V2DF(700,454)),
						g_screen.convertPixelsToCartesian(V2DF(722,435)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(677,399)),
						g_screen.convertPixelsToCartesian(V2DF(698,440)),
						g_screen.convertPixelsToCartesian(V2DF(691,404)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(677,399)),
						g_screen.convertPixelsToCartesian(V2DF(671,421)),
						g_screen.convertPixelsToCartesian(V2DF(698,440)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(671,421)),
						g_screen.convertPixelsToCartesian(V2DF(701,472)),
						g_screen.convertPixelsToCartesian(V2DF(698,440)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(701,472)),
						g_screen.convertPixelsToCartesian(V2DF(671,421)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(661,519)),
						g_screen.convertPixelsToCartesian(V2DF(701,472)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(634,523)),
						g_screen.convertPixelsToCartesian(V2DF(661,519)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(605,447)),
						g_screen.convertPixelsToCartesian(V2DF(634,523)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(614,418)),
						g_screen.convertPixelsToCartesian(V2DF(605,447)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(607,391)),
						g_screen.convertPixelsToCartesian(V2DF(614,418)));
	board.get(ID_S_AFRICA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(653,414)),
						g_screen.convertPixelsToCartesian(V2DF(644,396)),
						g_screen.convertPixelsToCartesian(V2DF(607,391)));
	board.get(ID_S_AFRICA)->addTriangle(tri);

	//Asia
		//1. Afghanistan
	board.get(ID_AFGHANISTAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(807,156)),22);
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_URAL));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_CHINA));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_INDIA));

	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(784,136)),
						g_screen.convertPixelsToCartesian(V2DF(801,198)),
						g_screen.convertPixelsToCartesian(V2DF(844,182)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
	//new
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(814,194)),
						g_screen.convertPixelsToCartesian(V2DF(842,183)),
						g_screen.convertPixelsToCartesian(V2DF(849,194)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);

	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(746,130)),
						g_screen.convertPixelsToCartesian(V2DF(728,142)),
						g_screen.convertPixelsToCartesian(V2DF(743,154)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(746,130)),
						g_screen.convertPixelsToCartesian(V2DF(743,154)),
						g_screen.convertPixelsToCartesian(V2DF(783,135)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(743,154)),
						g_screen.convertPixelsToCartesian(V2DF(770,195)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(770,195)),
						g_screen.convertPixelsToCartesian(V2DF(780,191)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(780,191)),
						g_screen.convertPixelsToCartesian(V2DF(802,204)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(780,191)),
						g_screen.convertPixelsToCartesian(V2DF(815,193)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(915,193)),
						g_screen.convertPixelsToCartesian(V2DF(849,194)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(849,194)),
						g_screen.convertPixelsToCartesian(V2DF(842,183)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(842,183)),
						g_screen.convertPixelsToCartesian(V2DF(865,170)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(865,170)),
						g_screen.convertPixelsToCartesian(V2DF(867,154)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(867,154)),
						g_screen.convertPixelsToCartesian(V2DF(828,121)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(783,135)),
						g_screen.convertPixelsToCartesian(V2DF(828,121)),
						g_screen.convertPixelsToCartesian(V2DF(781,120)));
	board.get(ID_AFGHANISTAN)->addTriangle(tri);
		//2. China
	board.get(ID_CHINA)->setArea(g_screen.convertPixelsToCartesian(V2DF(940,208)),22);
	board.get(ID_CHINA)->addConnection(board.get(ID_SIAM));
	board.get(ID_CHINA)->addConnection(board.get(ID_INDIA));
	board.get(ID_CHINA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_CHINA)->addConnection(board.get(ID_URAL));
	board.get(ID_CHINA)->addConnection(board.get(ID_SIBERIA));
	board.get(ID_CHINA)->addConnection(board.get(ID_MONGOLIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(881,143)),
						g_screen.convertPixelsToCartesian(V2DF(867,155)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(867,155)),
						g_screen.convertPixelsToCartesian(V2DF(865,170)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(865,170)),
						g_screen.convertPixelsToCartesian(V2DF(843,184)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(834,184)),
						g_screen.convertPixelsToCartesian(V2DF(849,194)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(849,194)),
						g_screen.convertPixelsToCartesian(V2DF(873,208)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(873,194)),
						g_screen.convertPixelsToCartesian(V2DF(871,222)));
	board.get(ID_CHINA)->addTriangle(tri);
		tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(871,222)),
						g_screen.convertPixelsToCartesian(V2DF(928,240)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(928,240)),
						g_screen.convertPixelsToCartesian(V2DF(940,232)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(940,232)),
						g_screen.convertPixelsToCartesian(V2DF(969,268)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(969,268)),
						g_screen.convertPixelsToCartesian(V2DF(986,259)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(986,259)),
						g_screen.convertPixelsToCartesian(V2DF(1010,273)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(1010,273)),
						g_screen.convertPixelsToCartesian(V2DF(1041,254)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,191)),
						g_screen.convertPixelsToCartesian(V2DF(1041,254)),
						g_screen.convertPixelsToCartesian(V2DF(1034,196)));
	board.get(ID_CHINA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1034,196)),
						g_screen.convertPixelsToCartesian(V2DF(1006,172)),
						g_screen.convertPixelsToCartesian(V2DF(978,193)));
	board.get(ID_CHINA)->addTriangle(tri);
		//3. India
	board.get(ID_INDIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(863,242)),22);
	board.get(ID_INDIA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_INDIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_INDIA)->addConnection(board.get(ID_SIAM));
	board.get(ID_INDIA)->addConnection(board.get(ID_MIDDLE_EAST));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(873,207)),
						g_screen.convertPixelsToCartesian(V2DF(848,195)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(848,195)),
						g_screen.convertPixelsToCartesian(V2DF(816,193)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(816,193)),
						g_screen.convertPixelsToCartesian(V2DF(801,204)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(801,204)),
						g_screen.convertPixelsToCartesian(V2DF(807,248)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(807,248)),
						g_screen.convertPixelsToCartesian(V2DF(852,271)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(852,271)),
						g_screen.convertPixelsToCartesian(V2DF(875,329)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(875,329)),
						g_screen.convertPixelsToCartesian(V2DF(932,267)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(872,223)),
						g_screen.convertPixelsToCartesian(V2DF(932,267)),
						g_screen.convertPixelsToCartesian(V2DF(928,239)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(928,239)),
						g_screen.convertPixelsToCartesian(V2DF(932,267)),
						g_screen.convertPixelsToCartesian(V2DF(940,232)));
	board.get(ID_INDIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(940,232)),
						g_screen.convertPixelsToCartesian(V2DF(932,267)),
						g_screen.convertPixelsToCartesian(V2DF(948,241)));
	board.get(ID_INDIA)->addTriangle(tri);
		//4. Irkutsk
	board.get(ID_IRKUTSK)->setArea(g_screen.convertPixelsToCartesian(V2DF(948,115)),22);
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_YAKUTSK));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_SIBERIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(911,78)),
						g_screen.convertPixelsToCartesian(V2DF(919,100)),
						g_screen.convertPixelsToCartesian(V2DF(934,98)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,94)),
						g_screen.convertPixelsToCartesian(V2DF(919,100)),
						g_screen.convertPixelsToCartesian(V2DF(972,108)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(919,100)),
						g_screen.convertPixelsToCartesian(V2DF(902,108)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(903,121)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(903,121)),
						g_screen.convertPixelsToCartesian(V2DF(919,129)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(919,129)),
						g_screen.convertPixelsToCartesian(V2DF(989,140)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(989,140)),
						g_screen.convertPixelsToCartesian(V2DF(989,126)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(989,126)),
						g_screen.convertPixelsToCartesian(V2DF(1000,122)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,108)),
						g_screen.convertPixelsToCartesian(V2DF(1000,122)),
						g_screen.convertPixelsToCartesian(V2DF(1021,114)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(903,121)),
						g_screen.convertPixelsToCartesian(V2DF(912,138)),
						g_screen.convertPixelsToCartesian(V2DF(919,129)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(903,121)),
						g_screen.convertPixelsToCartesian(V2DF(882,129)),
						g_screen.convertPixelsToCartesian(V2DF(912,138)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(882,129)),
						g_screen.convertPixelsToCartesian(V2DF(884,141)),
						g_screen.convertPixelsToCartesian(V2DF(895,133)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1021,114)),
						g_screen.convertPixelsToCartesian(V2DF(1000,122)),
						g_screen.convertPixelsToCartesian(V2DF(1037,144)));
	board.get(ID_IRKUTSK)->addTriangle(tri);
		//5. Japan
	board.get(ID_JAPAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(1103,198)),22);
	board.get(ID_JAPAN)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_JAPAN)->addConnection(board.get(ID_MONGOLIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1089,158)),
						g_screen.convertPixelsToCartesian(V2DF(1093,176)),
						g_screen.convertPixelsToCartesian(V2DF(1109,169)));
	board.get(ID_JAPAN)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1102,172)),
						g_screen.convertPixelsToCartesian(V2DF(1072,214)),
						g_screen.convertPixelsToCartesian(V2DF(1080,225)));
	board.get(ID_JAPAN)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1102,172)),
						g_screen.convertPixelsToCartesian(V2DF(1080,225)),
						g_screen.convertPixelsToCartesian(V2DF(1111,203)));
	board.get(ID_JAPAN)->addTriangle(tri);
		//6. Kamchatka
	board.get(ID_KAMCHATKA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1089,71)),22);
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_JAPAN));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_YAKUTSK));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_ALASKA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1009,102)),
						g_screen.convertPixelsToCartesian(V2DF(1014,114)),
						g_screen.convertPixelsToCartesian(V2DF(1024,114)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1009,102)),
						g_screen.convertPixelsToCartesian(V2DF(1023,116)),
						g_screen.convertPixelsToCartesian(V2DF(1034,117)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1034,117)),
						g_screen.convertPixelsToCartesian(V2DF(1010,102)),
						g_screen.convertPixelsToCartesian(V2DF(1059,58)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1034,117)),
						g_screen.convertPixelsToCartesian(V2DF(1059,58)),
						g_screen.convertPixelsToCartesian(V2DF(1109,59)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1034,117)),
						g_screen.convertPixelsToCartesian(V2DF(1109,59)),
						g_screen.convertPixelsToCartesian(V2DF(1102,89)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1109,59)),
						g_screen.convertPixelsToCartesian(V2DF(1097,107)),
						g_screen.convertPixelsToCartesian(V2DF(1123,107)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1123,107)),
						g_screen.convertPixelsToCartesian(V2DF(1097,107)),
						g_screen.convertPixelsToCartesian(V2DF(1126,135)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1109,59)),
						g_screen.convertPixelsToCartesian(V2DF(1123,107)),
						g_screen.convertPixelsToCartesian(V2DF(1166,69)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1023,116)),
						g_screen.convertPixelsToCartesian(V2DF(1038,143)),
						g_screen.convertPixelsToCartesian(V2DF(1064,119)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1064,119)),
						g_screen.convertPixelsToCartesian(V2DF(1038,143)),
						g_screen.convertPixelsToCartesian(V2DF(1056,146)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1064,119)),
						g_screen.convertPixelsToCartesian(V2DF(1056,146)),
						g_screen.convertPixelsToCartesian(V2DF(1093,148)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1056,146)),
						g_screen.convertPixelsToCartesian(V2DF(1093,148)),
						g_screen.convertPixelsToCartesian(V2DF(1058,166)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1093,148)),
						g_screen.convertPixelsToCartesian(V2DF(1058,166)),
						g_screen.convertPixelsToCartesian(V2DF(1066,172)));
	board.get(ID_KAMCHATKA)->addTriangle(tri);
	//7. Middle East
	board.get(ID_MIDDLE_EAST)->setArea(g_screen.convertPixelsToCartesian(V2DF(731,217)),22);
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_INDIA));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_EGYPT));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_E_AFRICA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(688,172)),
						g_screen.convertPixelsToCartesian(V2DF(669,201)),
						g_screen.convertPixelsToCartesian(V2DF(658,182)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(688,172)),
						g_screen.convertPixelsToCartesian(V2DF(669,201)),
						g_screen.convertPixelsToCartesian(V2DF(699,199)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(688,172)),
						g_screen.convertPixelsToCartesian(V2DF(699,199)),
						g_screen.convertPixelsToCartesian(V2DF(717,176)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(717,176)),
						g_screen.convertPixelsToCartesian(V2DF(699,199)),
						g_screen.convertPixelsToCartesian(V2DF(749,190)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(749,190)),
						g_screen.convertPixelsToCartesian(V2DF(699,199)),
						g_screen.convertPixelsToCartesian(V2DF(800,204)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(800,204)),
						g_screen.convertPixelsToCartesian(V2DF(780,190)),
						g_screen.convertPixelsToCartesian(V2DF(772,195)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(699,199)),
						g_screen.convertPixelsToCartesian(V2DF(694,225)),
						g_screen.convertPixelsToCartesian(V2DF(800,204)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(694,225)),
						g_screen.convertPixelsToCartesian(V2DF(800,204)),
						g_screen.convertPixelsToCartesian(V2DF(807,249)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(694,225)),
						g_screen.convertPixelsToCartesian(V2DF(807,249)),
						g_screen.convertPixelsToCartesian(V2DF(800,266)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(694,225)),
						g_screen.convertPixelsToCartesian(V2DF(800,266)),
						g_screen.convertPixelsToCartesian(V2DF(779,295)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(694,225)),
						g_screen.convertPixelsToCartesian(V2DF(779,295)),
						g_screen.convertPixelsToCartesian(V2DF(737,308)));
	board.get(ID_MIDDLE_EAST)->addTriangle(tri);
		//8. Mongolia
	board.get(ID_MONGOLIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(966,160)),22);
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_JAPAN));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_SIBERIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,190)),
						g_screen.convertPixelsToCartesian(V2DF(881,141)),
						g_screen.convertPixelsToCartesian(V2DF(913,138)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,190)),
						g_screen.convertPixelsToCartesian(V2DF(913,138)),
						g_screen.convertPixelsToCartesian(V2DF(919,129)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,190)),
						g_screen.convertPixelsToCartesian(V2DF(919,129)),
						g_screen.convertPixelsToCartesian(V2DF(989,140)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,190)),
						g_screen.convertPixelsToCartesian(V2DF(989,140)),
						g_screen.convertPixelsToCartesian(V2DF(1007,173)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(950,190)),
						g_screen.convertPixelsToCartesian(V2DF(1007,173)),
						g_screen.convertPixelsToCartesian(V2DF(979,193)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(881,141)),
						g_screen.convertPixelsToCartesian(V2DF(913,138)),
						g_screen.convertPixelsToCartesian(V2DF(895,133)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1001,122)),
						g_screen.convertPixelsToCartesian(V2DF(987,125)),
						g_screen.convertPixelsToCartesian(V2DF(1037,143)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1037,143)),
						g_screen.convertPixelsToCartesian(V2DF(987,125)),
						g_screen.convertPixelsToCartesian(V2DF(989,140)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(989,140)),
						g_screen.convertPixelsToCartesian(V2DF(1007,173)),
						g_screen.convertPixelsToCartesian(V2DF(1056,146)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1056,146)),
						g_screen.convertPixelsToCartesian(V2DF(1007,173)),
						g_screen.convertPixelsToCartesian(V2DF(1063,208)));
	board.get(ID_MONGOLIA)->addTriangle(tri);
		//9. Siam
	board.get(ID_SIAM)->setArea(g_screen.convertPixelsToCartesian(V2DF(974,284)),22);
	board.get(ID_SIAM)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_SIAM)->addConnection(board.get(ID_CHINA));
	board.get(ID_SIAM)->addConnection(board.get(ID_INDIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(948,241)),
						g_screen.convertPixelsToCartesian(V2DF(934,268)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(934,268)),
						g_screen.convertPixelsToCartesian(V2DF(944,287)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(944,287)),
						g_screen.convertPixelsToCartesian(V2DF(967,310)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(967,310)),
						g_screen.convertPixelsToCartesian(V2DF(970,302)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(970,302)),
						g_screen.convertPixelsToCartesian(V2DF(996,325)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(996,325)),
						g_screen.convertPixelsToCartesian(V2DF(1010,308)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(1010,308)),
						g_screen.convertPixelsToCartesian(V2DF(995,265)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(967,268)),
						g_screen.convertPixelsToCartesian(V2DF(995,265)),
						g_screen.convertPixelsToCartesian(V2DF(986,259)));
	board.get(ID_SIAM)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(970,302)),
						g_screen.convertPixelsToCartesian(V2DF(962,324)),
						g_screen.convertPixelsToCartesian(V2DF(989,358)));
	board.get(ID_SIAM)->addTriangle(tri);
		//10. Siberia
	board.get(ID_SIBERIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(863,67)),22);
	board.get(ID_SIBERIA)->addConnection(board.get(ID_URAL));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_YAKUTSK));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(918,99)),
						g_screen.convertPixelsToCartesian(V2DF(910,78)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(910,78)),
						g_screen.convertPixelsToCartesian(V2DF(883,33)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(883,33)),
						g_screen.convertPixelsToCartesian(V2DF(851,28)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(851,28)),
						g_screen.convertPixelsToCartesian(V2DF(869,108)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(869,108)),
						g_screen.convertPixelsToCartesian(V2DF(872,128)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(872,128)),
						g_screen.convertPixelsToCartesian(V2DF(886,128)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(902,108)),
						g_screen.convertPixelsToCartesian(V2DF(886,128)),
						g_screen.convertPixelsToCartesian(V2DF(902,121)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(871,127)),
						g_screen.convertPixelsToCartesian(V2DF(861,135)),
						g_screen.convertPixelsToCartesian(V2DF(876,147)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(871,127)),
						g_screen.convertPixelsToCartesian(V2DF(876,147)),
						g_screen.convertPixelsToCartesian(V2DF(884,141)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(871,127)),
						g_screen.convertPixelsToCartesian(V2DF(884,141)),
						g_screen.convertPixelsToCartesian(V2DF(882,128)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(871,127)),
						g_screen.convertPixelsToCartesian(V2DF(869,108)),
						g_screen.convertPixelsToCartesian(V2DF(857,111)));
	board.get(ID_SIBERIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(851,28)),
						g_screen.convertPixelsToCartesian(V2DF(801,47)),
						g_screen.convertPixelsToCartesian(V2DF(869,108)));
	board.get(ID_SIBERIA)->addTriangle(tri);
		//11. Ural
	board.get(ID_URAL)->setArea(g_screen.convertPixelsToCartesian(V2DF(803,94)),22);
	board.get(ID_URAL)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_URAL)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_URAL)->addConnection(board.get(ID_CHINA));
	board.get(ID_URAL)->addConnection(board.get(ID_SIBERIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(776,44)),
						g_screen.convertPixelsToCartesian(V2DF(760,57)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(760,57)),
						g_screen.convertPixelsToCartesian(V2DF(766,68)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(766,68)),
						g_screen.convertPixelsToCartesian(V2DF(749,80)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(749,80)),
						g_screen.convertPixelsToCartesian(V2DF(773,120)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(773,120)),
						g_screen.convertPixelsToCartesian(V2DF(828,121)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(828,121)),
						g_screen.convertPixelsToCartesian(V2DF(857,111)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(857,111)),
						g_screen.convertPixelsToCartesian(V2DF(835,78)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(835,78)),
						g_screen.convertPixelsToCartesian(V2DF(801,46)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(791,69)),
						g_screen.convertPixelsToCartesian(V2DF(801,46)),
						g_screen.convertPixelsToCartesian(V2DF(787,49)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(835,78)),
						g_screen.convertPixelsToCartesian(V2DF(857,111)),
						g_screen.convertPixelsToCartesian(V2DF(870,108)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(857,111)),
						g_screen.convertPixelsToCartesian(V2DF(828,121)),
						g_screen.convertPixelsToCartesian(V2DF(850,141)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(857,111)),
						g_screen.convertPixelsToCartesian(V2DF(850,141)),
						g_screen.convertPixelsToCartesian(V2DF(871,127)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(850,141)),
						g_screen.convertPixelsToCartesian(V2DF(875,148)),
						g_screen.convertPixelsToCartesian(V2DF(861,135)));
	board.get(ID_URAL)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(850,141)),
						g_screen.convertPixelsToCartesian(V2DF(875,148)),
						g_screen.convertPixelsToCartesian(V2DF(867,154)));
	board.get(ID_URAL)->addTriangle(tri);
		//12. Yakutsk
	board.get(ID_YAKUTSK)->setArea(g_screen.convertPixelsToCartesian(V2DF(971,74)),22);
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_SIBERIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(888,43)),
						g_screen.convertPixelsToCartesian(V2DF(910,79)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(910,79)),
						g_screen.convertPixelsToCartesian(V2DF(935,97)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(935,97)),
						g_screen.convertPixelsToCartesian(V2DF(951,94)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(951,94)),
						g_screen.convertPixelsToCartesian(V2DF(971,108)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(971,108)),
						g_screen.convertPixelsToCartesian(V2DF(998,112)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(990,45)),
						g_screen.convertPixelsToCartesian(V2DF(998,112)),
						g_screen.convertPixelsToCartesian(V2DF(1058,58)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(998,112)),
						g_screen.convertPixelsToCartesian(V2DF(1015,114)),
						g_screen.convertPixelsToCartesian(V2DF(1010,102)));
	board.get(ID_YAKUTSK)->addTriangle(tri);
	//Oceania
		//1. Eastern Australia
	board.get(ID_E_AUSTRALIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1137, 465)),22);
	board.get(ID_E_AUSTRALIA)->addConnection(board.get(ID_W_AUSTRALIA));
	board.get(ID_E_AUSTRALIA)->addConnection(board.get(ID_N_GUINEA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1090,432)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1090,432)),
						g_screen.convertPixelsToCartesian(V2DF(1111,410)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1090,432)),
						g_screen.convertPixelsToCartesian(V2DF(1135,446)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1135,446)),
						g_screen.convertPixelsToCartesian(V2DF(1182,485)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1182,485)),
						g_screen.convertPixelsToCartesian(V2DF(1142,539)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1126,485)),
						g_screen.convertPixelsToCartesian(V2DF(1142,539)),
						g_screen.convertPixelsToCartesian(V2DF(1106,539)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1113,568)),
						g_screen.convertPixelsToCartesian(V2DF(1142,539)),
						g_screen.convertPixelsToCartesian(V2DF(1106,539)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1147,414)),
						g_screen.convertPixelsToCartesian(V2DF(1182,485)),
						g_screen.convertPixelsToCartesian(V2DF(1142,539)));
	board.get(ID_E_AUSTRALIA)->addTriangle(tri);
		//2. Indonesia
	board.get(ID_INDONESIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1033,362)),22);
	board.get(ID_INDONESIA)->addConnection(board.get(ID_SIAM));
	board.get(ID_INDONESIA)->addConnection(board.get(ID_N_GUINEA));
	board.get(ID_INDONESIA)->addConnection(board.get(ID_W_AUSTRALIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(953,338)),
						g_screen.convertPixelsToCartesian(V2DF(972,378)),
						g_screen.convertPixelsToCartesian(V2DF(990,365)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(972,378)),
						g_screen.convertPixelsToCartesian(V2DF(990,365)),
						g_screen.convertPixelsToCartesian(V2DF(996,395)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(994,396)),
						g_screen.convertPixelsToCartesian(V2DF(1029,393)),
						g_screen.convertPixelsToCartesian(V2DF(1050,408)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1029,393)),
						g_screen.convertPixelsToCartesian(V2DF(1055,412)),
						g_screen.convertPixelsToCartesian(V2DF(1086,404)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1012,383)),
						g_screen.convertPixelsToCartesian(V2DF(1050,327)),
						g_screen.convertPixelsToCartesian(V2DF(1007,350)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1012,383)),
						g_screen.convertPixelsToCartesian(V2DF(1050,327)),
						g_screen.convertPixelsToCartesian(V2DF(1048,385)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1055,358)),
						g_screen.convertPixelsToCartesian(V2DF(1051,396)),
						g_screen.convertPixelsToCartesian(V2DF(1080,358)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1078,301)),
						g_screen.convertPixelsToCartesian(V2DF(1055,320)),
						g_screen.convertPixelsToCartesian(V2DF(1051,278)));
	board.get(ID_INDONESIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1078,301)),
						g_screen.convertPixelsToCartesian(V2DF(1055,320)),
						g_screen.convertPixelsToCartesian(V2DF(1084,343)));
	board.get(ID_INDONESIA)->addTriangle(tri);

		//3. New Guinea
	board.get(ID_N_GUINEA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1146,387)),22);
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_E_AUSTRALIA));
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_W_AUSTRALIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1096,346)),
						g_screen.convertPixelsToCartesian(V2DF(1084,362)),
						g_screen.convertPixelsToCartesian(V2DF(1095,369)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1099,374)),
						g_screen.convertPixelsToCartesian(V2DF(1085,380)),
						g_screen.convertPixelsToCartesian(V2DF(1103,382)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1097,366)),
						g_screen.convertPixelsToCartesian(V2DF(1132,405)),
						g_screen.convertPixelsToCartesian(V2DF(1154,370)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1132,405)),
						g_screen.convertPixelsToCartesian(V2DF(1154,370)),
						g_screen.convertPixelsToCartesian(V2DF(1190,416)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1184,366)),
						g_screen.convertPixelsToCartesian(V2DF(1171,392)),
						g_screen.convertPixelsToCartesian(V2DF(1226,418)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1226,396)),
						g_screen.convertPixelsToCartesian(V2DF(1224,417)),
						g_screen.convertPixelsToCartesian(V2DF(1207,395)));
	board.get(ID_N_GUINEA)->addTriangle(tri);
		//4. Western Australia
	board.get(ID_W_AUSTRALIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1051,490)),22);
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_N_GUINEA));
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_E_AUSTRALIA));
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1090,432)),
						g_screen.convertPixelsToCartesian(V2DF(1082,427)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1082,427)),
						g_screen.convertPixelsToCartesian(V2DF(1020,466)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1020,466)),
						g_screen.convertPixelsToCartesian(V2DF(1012,528)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1012,528)),
						g_screen.convertPixelsToCartesian(V2DF(1082,508)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1074,480)),
						g_screen.convertPixelsToCartesian(V2DF(1082,508)),
						g_screen.convertPixelsToCartesian(V2DF(1125,485)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);
	tri = new Triangle(g_screen.convertPixelsToCartesian(V2DF(1106,539)),
						g_screen.convertPixelsToCartesian(V2DF(1082,508)),
						g_screen.convertPixelsToCartesian(V2DF(1125,485)));
	board.get(ID_W_AUSTRALIA)->addTriangle(tri);

	for(int i = 0; i < board.size(); ++i)
		board.get(i)->useContinentColorTri();
	//for(int i = 0; i < board.size(); ++i)
	//	printf("i == %d, ID == %d, contID == %d, #connect == %d, #troop == %d\n", i, board.get(i)->getID(), board.get(i)->getContinent(), board.get(i)->getNumberConnections(), board.get(i)->getTroops());
}
void initPlayers()
{	
	//OLD CODE THAT NEEDED REMOVED
	/*
	do
	{
		printf("How many players (%d-%d)?\n", PLAYERS_MIN, PLAYERS_MAX);
		cin >> flags[FLAG_PLAYERS];
	}while(flags[FLAG_PLAYERS] < PLAYERS_MIN || flags[FLAG_PLAYERS] > PLAYERS_MAX);
	//printf("players == %d\n", flags[FLAG_PLAYERS]);
	*/

	//NEW CODE JOHN NEEDED ADDED!
	char a_ch[BUFFER_SIZE];
	do
	{
		printf("How many players (%d-%d)?\n", PLAYERS_MIN, PLAYERS_MAX);
		cin >> a_ch;
		flags[FLAG_PLAYERS] = atoi(a_ch);
	}while(flags[FLAG_PLAYERS] < PLAYERS_MIN || flags[FLAG_PLAYERS] > PLAYERS_MAX);
	////followed by the rest of the function
	Player * ply;

	short startWithTroops;
	switch(flags[FLAG_PLAYERS])
	{
	case NUM_PLAYERS_TWO:
		startWithTroops = TROOPS_PLAYERS_TWO;
		break;
	case NUM_PLAYERS_THREE:
		startWithTroops = TROOPS_PLAYERS_THREE;
		break;
	case NUM_PLAYERS_FOUR:
		startWithTroops = TROOPS_PLAYERS_FOUR;
		break;
	case NUM_PLAYERS_FIVE:
		startWithTroops = TROOPS_PLAYERS_FIVE;
		break;
	case NUM_PLAYERS_SIX:
		startWithTroops = TROOPS_PLAYERS_SIX;
		break;
	}
	for(int i = 0; i < flags[FLAG_PLAYERS]; ++i)
	{
		char ans;
		do{
			printf("Should Player %d be AI controlled(Y/N)?\n", i+1);
			cin >> ans;
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');
		if(ans == 'n' || ans == 'N')
			ply = new Player(startWithTroops,players.size());
		else
			ply = new PlayerAI(startWithTroops,players.size());
		players.add(ply);
		//printf("numCards == %d\n", players.get(i)->getNumCards());
	}
	//for(int i = 0; i < players.size(); ++i)
	//	printf("Is Player %d AI controlled == %d\n", i+1, players.get(i)->isAI());
	flags[FLAG_CURRENT_PLAYER] = PLAYER_ONE;
}
void initDeck()
{
	Card * crd;
	for(int i = 0; i < CARD_NUM_IN_DECK_WO_WILD; ++i)
	{
		crd = new Card((i % 3), i, i);
		deck.add(crd);
	}
	for(int i = CARD_NUM_IN_DECK_WO_WILD; i < CARD_NUM_IN_DECK; ++i)
	{
		crd = new Card(CARD_ID_WILD, CARD_TERRITORY_NONE, i);
		deck.add(crd);
	}
	flags[FLAG_CARD_SET] = 0;
	flags[FLAG_DRAW_CARD] = true;
	flags[FLAG_FIRST_SET_IN_TURN] = true;
	//for(int i = 0; i < deck.size(); ++i)
	//	printf("id == %d, ter == %d, unit == %d\n", deck.get(i)->getCardID(), deck.get(i)->getTerritoryID(), deck.get(i)->getUnit());
}
#include "draw.h"
#include "eventhandlers.h"

/** call this function every value seconds*/
void updateTimerFunction(int value)
{
	/** keeps track of when the update method was called last */
	static clock_t g_lastTime = 0;
	// what time is it now?
	clock_t now = clock();
	// how much time has passed since update was called?
	clock_t passed = now-g_lastTime;
	// if update based on time
	if(update(passed))
	{
		// ask to refresh the display
		glutPostRedisplay();
	}
	// remember this last time that update started.
	g_lastTime = now;
	now = clock();
	// calc how long it took update to process, and factor that into the next wait
	passed = now - g_lastTime;
	int waitToCall = value-passed;
	if(waitToCall < 0)waitToCall = 0;
	// queue update again, factoring in the time update just took
	glutTimerFunc(waitToCall, updateTimerFunction, value);
}

void init()
{
	// setup the screen using the graphics context
	g_screen.glSetupScreen();
	// position the window
	glutInitWindowPosition(INIT_WINDOW_X,INIT_WINDOW_Y);
	// define the drawing mode
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//Create our window
	glutCreateWindow("Risk");
	// setup the call-back functions
    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(draggedMotion);
	glutMouseFunc(mouse);
	initBoard();
	initDeck();
	initPlayers();
	flags[FLAG_GAME_STATE] = STATE_INIT_PLACEMENT_CLAIM;
	flags[FLAG_UPDATE_GAME_STATE] = false;
	flags[FLAG_PARAMS_SET] = false;
}

int main(int argc, char ** argv)
{
	seedRandom(time(NULL));
	// initialize GLUT
	glutInit(&argc, argv);
	// initialize the application
	init();
	// start the update timer-thread game-loop
	glutTimerFunc(0, updateTimerFunction, TIMER_VALUE);

	// abstracted game loop that we don't get to see!!!
    glutMainLoop();

	for(int i = 0; i < board.size(); ++i)
		delete board.get(i);
	for(int i = 0; i < players.size(); ++i)
		delete players.get(i);
	for(int i = 0; i < deck.size(); ++i)
		delete deck.get(i);

	return 0;
}