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
#include "player.h"
#include "playerai.h"
#include "card.h"

// GLUT will not give access to the main loop, some variables MUST be global. :(
GLUTRenderingContext g_screen(V2DF(SCREEN_WIDTH,SCREEN_HEIGHT), V2DF(SCREEN_MIN_X,SCREEN_MIN_Y), V2DF(SCREEN_MAX_X,SCREEN_MAX_Y));
TemplateArray<Territory *> board;
TemplateArray<Player *> players;
TemplateArray<Card *> deck;
short flags[FLAGS_NUM];

void initBoard()
{
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

	//North America
		//1. Alaska
	board.get(ID_ALASKA)->setArea(V2DF(80,550),30);
	board.get(ID_ALASKA)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_ALASKA)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ALASKA)->addConnection(board.get(ID_KAMCHATKA));
		//2. Alberta
	board.get(ID_ALBERTA)->setArea(V2DF(165,505),20);
	board.get(ID_ALBERTA)->addConnection(board.get(ID_ALASKA));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_ALBERTA)->addConnection(board.get(ID_W_US));
		//3. Central America
	board.get(ID_C_AMERICA)->setArea(V2DF(190,360),45);
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_E_US));
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_W_US));
	board.get(ID_C_AMERICA)->addConnection(board.get(ID_VENEZUELA));
		//4. Eastern United States
	board.get(ID_E_US)->setArea(V2DF(220,440),40);
	board.get(ID_E_US)->addConnection(board.get(ID_C_AMERICA));
	board.get(ID_E_US)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_E_US)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_E_US)->addConnection(board.get(ID_W_US));
		//5. Greenland
	board.get(ID_GREENLAND)->setArea(V2DF(465,580),40);
	board.get(ID_GREENLAND)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_ONTARIO));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_GREENLAND)->addConnection(board.get(ID_ICELAND));
		//6. Northwest Territory
	board.get(ID_NW_TERRITORY)->setArea(V2DF(215,565),30);
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ALASKA));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_NW_TERRITORY)->addConnection(board.get(ID_ONTARIO));
		//7. Ontario
	board.get(ID_ONTARIO)->setArea(V2DF(245,505),25);
	board.get(ID_ONTARIO)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_E_US));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_NW_TERRITORY));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_QUEBEC));
	board.get(ID_ONTARIO)->addConnection(board.get(ID_W_US));
		//8. Quebec
	board.get(ID_QUEBEC)->setArea(V2DF(310,500),40);
	board.get(ID_QUEBEC)->addConnection(board.get(ID_E_US));
	board.get(ID_QUEBEC)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_QUEBEC)->addConnection(board.get(ID_ONTARIO));
		//9. Western United States
	board.get(ID_W_US)->setArea(V2DF(140,450),40);
	board.get(ID_W_US)->addConnection(board.get(ID_ALBERTA));
	board.get(ID_W_US)->addConnection(board.get(ID_C_AMERICA));
	board.get(ID_W_US)->addConnection(board.get(ID_E_US));
	board.get(ID_W_US)->addConnection(board.get(ID_ONTARIO));

	//South America
		//1. Argentina
	board.get(ID_ARGENTINA)->setArea(g_screen.convertPixelsToCartesian(V2DF(300,514)),40);
	board.get(ID_ARGENTINA)->addConnection(board.get(ID_PERU));
	board.get(ID_ARGENTINA)->addConnection(board.get(ID_BRAZIL));
		//2. Brazil
	board.get(ID_BRAZIL)->setArea(g_screen.convertPixelsToCartesian(V2DF(344,411)),40);
	board.get(ID_BRAZIL)->addConnection(board.get(ID_ARGENTINA));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_PERU));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_VENEZUELA));
	board.get(ID_BRAZIL)->addConnection(board.get(ID_N_AFRICA));
		//3. Peru
	board.get(ID_PERU)->setArea(g_screen.convertPixelsToCartesian(V2DF(285,445)),25);
	board.get(ID_PERU)->addConnection(board.get(ID_ARGENTINA));
	board.get(ID_PERU)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_PERU)->addConnection(board.get(ID_VENEZUELA));
		//4. Venezuela
	board.get(ID_VENEZUELA)->setArea(g_screen.convertPixelsToCartesian(V2DF(265,345)),35);
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_PERU));
	board.get(ID_VENEZUELA)->addConnection(board.get(ID_C_AMERICA));

	//Europe
		//1. Great Britain
	board.get(ID_GREAT_BRITIAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(544,123)),20);
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_ICELAND));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_GREAT_BRITIAN)->addConnection(board.get(ID_W_EUROPE));
		//2. Iceland
	board.get(ID_ICELAND)->setArea(g_screen.convertPixelsToCartesian(V2DF(525,78)),15);
	board.get(ID_ICELAND)->addConnection(board.get(ID_GREENLAND));
	board.get(ID_ICELAND)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_ICELAND)->addConnection(board.get(ID_SCANDINAVIA));
		//3. Northern Europe
	board.get(ID_N_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(613,134)),20);
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_N_EUROPE)->addConnection(board.get(ID_W_EUROPE));
		//4. Scandinavia
	board.get(ID_SCANDINAVIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(605,85)),20);
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_ICELAND));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_SCANDINAVIA)->addConnection(board.get(ID_GREAT_BRITIAN));
		//5. Southern Europe
	board.get(ID_S_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(642,167)),20);
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_EGYPT));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_S_EUROPE)->addConnection(board.get(ID_W_EUROPE));
		//6. Russia
	board.get(ID_RUSSIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(700,112)),35);
	board.get(ID_RUSSIA)->addConnection(board.get(ID_URAL));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_SCANDINAVIA));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_RUSSIA)->addConnection(board.get(ID_S_EUROPE));
		//7. Western Europe
	board.get(ID_W_EUROPE)->setArea(g_screen.convertPixelsToCartesian(V2DF(560,165)),20);
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_N_EUROPE));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_GREAT_BRITIAN));
	board.get(ID_W_EUROPE)->addConnection(board.get(ID_S_EUROPE));

	//Africa
		//1. Congo
	board.get(ID_CONGO)->setArea(g_screen.convertPixelsToCartesian(V2DF(649,366)),30);
	board.get(ID_CONGO)->addConnection(board.get(ID_S_AFRICA));
	board.get(ID_CONGO)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_CONGO)->addConnection(board.get(ID_E_AFRICA));
		//2. East Africa
	board.get(ID_E_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(704,318)),30);
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_EGYPT));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_N_AFRICA));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_MADAGASCAR));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_CONGO));
	board.get(ID_E_AFRICA)->addConnection(board.get(ID_S_AFRICA));
		//3. Egypt
	board.get(ID_EGYPT)->setArea(g_screen.convertPixelsToCartesian(V2DF(647,242)),30);
	board.get(ID_EGYPT)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_EGYPT)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_EGYPT)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_EGYPT)->addConnection(board.get(ID_N_AFRICA));
		//4. Madagascar
	board.get(ID_MADAGASCAR)->setArea(g_screen.convertPixelsToCartesian(V2DF(748,448)),20);
	board.get(ID_MADAGASCAR)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_MADAGASCAR)->addConnection(board.get(ID_S_AFRICA));
		//5. North Africa
	board.get(ID_N_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(566,290)),50);
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_BRAZIL));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_W_EUROPE));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_EGYPT));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_N_AFRICA)->addConnection(board.get(ID_CONGO));
		//6. South Africa
	board.get(ID_S_AFRICA)->setArea(g_screen.convertPixelsToCartesian(V2DF(652,455)),35);
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_E_AFRICA));
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_CONGO));
	board.get(ID_S_AFRICA)->addConnection(board.get(ID_MADAGASCAR));

	//Asia
		//1. Afghanistan
	board.get(ID_AFGHANISTAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(806,162)),35);
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_URAL));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_CHINA));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_MIDDLE_EAST));
	board.get(ID_AFGHANISTAN)->addConnection(board.get(ID_INDIA));
		//2. China
	board.get(ID_CHINA)->setArea(g_screen.convertPixelsToCartesian(V2DF(937,207)),35);
	board.get(ID_CHINA)->addConnection(board.get(ID_SIAM));
	board.get(ID_CHINA)->addConnection(board.get(ID_INDIA));
	board.get(ID_CHINA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_CHINA)->addConnection(board.get(ID_URAL));
	board.get(ID_CHINA)->addConnection(board.get(ID_SIBERIA));
	board.get(ID_CHINA)->addConnection(board.get(ID_MONGOLIA));
		//3. India
	board.get(ID_INDIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(865,238)),35);
	board.get(ID_INDIA)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_INDIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_INDIA)->addConnection(board.get(ID_SIAM));
	board.get(ID_INDIA)->addConnection(board.get(ID_MIDDLE_EAST));
		//4. Irkutsk
	board.get(ID_IRKUTSK)->setArea(g_screen.convertPixelsToCartesian(V2DF(940,122)),25);
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_YAKUTSK));
	board.get(ID_IRKUTSK)->addConnection(board.get(ID_SIBERIA));
		//5. Japan
	board.get(ID_JAPAN)->setArea(g_screen.convertPixelsToCartesian(V2DF(1099,201)),25);
	board.get(ID_JAPAN)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_JAPAN)->addConnection(board.get(ID_MONGOLIA));
		//6. Kamchatka
	board.get(ID_KAMCHATKA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1062,86)),30);
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_JAPAN));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_YAKUTSK));
	board.get(ID_KAMCHATKA)->addConnection(board.get(ID_ALASKA));
		//7. Middle East
	board.get(ID_MIDDLE_EAST)->setArea(g_screen.convertPixelsToCartesian(V2DF(726,228)),35);
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_INDIA));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_S_EUROPE));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_EGYPT));
	board.get(ID_MIDDLE_EAST)->addConnection(board.get(ID_E_AFRICA));
		//8. Mongolia
	board.get(ID_MONGOLIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(985,160)),30);
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_JAPAN));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_MONGOLIA)->addConnection(board.get(ID_SIBERIA));
		//9. Siam
	board.get(ID_SIAM)->setArea(g_screen.convertPixelsToCartesian(V2DF(973,284)),25);
	board.get(ID_SIAM)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_SIAM)->addConnection(board.get(ID_CHINA));
	board.get(ID_SIAM)->addConnection(board.get(ID_INDIA));
		//10. Siberia
	board.get(ID_SIBERIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(867,72)),35);
	board.get(ID_SIBERIA)->addConnection(board.get(ID_URAL));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_CHINA));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_MONGOLIA));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_SIBERIA)->addConnection(board.get(ID_YAKUTSK));
		//11. Ural
	board.get(ID_URAL)->setArea(g_screen.convertPixelsToCartesian(V2DF(775,92)),35);
	board.get(ID_URAL)->addConnection(board.get(ID_RUSSIA));
	board.get(ID_URAL)->addConnection(board.get(ID_AFGHANISTAN));
	board.get(ID_URAL)->addConnection(board.get(ID_CHINA));
	board.get(ID_URAL)->addConnection(board.get(ID_SIBERIA));
		//12. Yakutsk
	board.get(ID_YAKUTSK)->setArea(g_screen.convertPixelsToCartesian(V2DF(974,71)),35);
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_KAMCHATKA));
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_IRKUTSK));
	board.get(ID_YAKUTSK)->addConnection(board.get(ID_SIBERIA));

	//Oceania
		//1. Eastern Australia
	board.get(ID_E_AUSTRALIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1140, 475)),40);
	board.get(ID_E_AUSTRALIA)->addConnection(board.get(ID_W_AUSTRALIA));
	board.get(ID_E_AUSTRALIA)->addConnection(board.get(ID_N_GUINEA));
		//2. Indonesia
	board.get(ID_INDONESIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1029,362)),30);
	board.get(ID_INDONESIA)->addConnection(board.get(ID_SIAM));
	board.get(ID_INDONESIA)->addConnection(board.get(ID_N_GUINEA));
	board.get(ID_INDONESIA)->addConnection(board.get(ID_W_AUSTRALIA));
		//3. New Guinea
	board.get(ID_N_GUINEA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1141,387)),30);
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_E_AUSTRALIA));
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_N_GUINEA)->addConnection(board.get(ID_W_AUSTRALIA));
		//4. Western Australia
	board.get(ID_W_AUSTRALIA)->setArea(g_screen.convertPixelsToCartesian(V2DF(1050,480)),40);
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_N_GUINEA));
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_INDONESIA));
	board.get(ID_W_AUSTRALIA)->addConnection(board.get(ID_E_AUSTRALIA));

	//for(int i = 0; i < board.size(); ++i)
	//	printf("i == %d, ID == %d, contID == %d, #connect == %d, #troop == %d\n", i, board.get(i)->getID(), board.get(i)->getContinent(), board.get(i)->getNumberConnections(), board.get(i)->getTroops());
}
void initPlayers()
{
	char a_ch[BUFFER_SIZE];
	do
	{
		printf("How many players (%d-%d)?\n", PLAYERS_MIN, PLAYERS_MAX);
		cin >> a_ch;
		flags[FLAG_PLAYERS] = atoi(a_ch);
	}while(flags[FLAG_PLAYERS] < PLAYERS_MIN || flags[FLAG_PLAYERS] > PLAYERS_MAX);
	//printf("players == %d\n", flags[FLAG_PLAYERS]);

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