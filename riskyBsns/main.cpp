#include <stdio.h>	// for printf()
#include <time.h>	// for clock()

#include "GLUTRenderingContext.h"
#include "random.h"

#define SCREEN_WIDTH			1230
#define SCREEN_HEIGHT			630
#define SCREEN_MAX_X			SCREEN_WIDTH
#define SCREEN_MAX_Y			SCREEN_HEIGHT
#define SCREEN_MIN_X			0
#define SCREEN_MIN_Y			0
#define	COLOR_ALPHA				1.0
#define COLOR_BLACK				.0,.0,.0
#define COLOR_CYAN				0xffff00
#define COLOR_GREY				.5,.5,.5
#define CONTINENT_ID_N_AMERICA	0
#define CONTINENT_ID_S_AMERICA	1
#define CONTINENT_ID_EUROPE		2
#define CONTINENT_ID_AFRICA		3
#define CONTINENT_ID_ASIA		4
#define CONTINENT_ID_OCEANIA	5
#define DASH_SIZE				.5
#define INIT_WINDOW_X			10
#define INIT_WINDOW_Y			50
#define OWNER_NONE				-1
#define TIMER_VALUE				20
#define TERRITORIES_N_AMERICA	9
#define TERRITORIES_S_AMERICA	4
#define TERRITORIES_EUROPE		7
#define TERRITORIES_AFRICA		6
#define TERRITORIES_ASIA		12
#define TERRITORIES_OCEANIA		4
#define TERRITORIES_TOTAL		(TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA + TERRITORIES_ASIA + TERRITORIES_OCEANIA)

#include "templatearray.h"
#include "territory.h"
#include "circle.h"

// GLUT will not give access to the main loop, some variables MUST be global. :(
GLUTRenderingContext g_screen(V2DF(SCREEN_WIDTH,SCREEN_HEIGHT), V2DF(SCREEN_MIN_X,SCREEN_MIN_Y), V2DF(SCREEN_MAX_X,SCREEN_MAX_Y));
TemplateArray<Territory *> territoryNodes;

void initTerritoryNodes()
{
	Territory * ter;

	//set continent ID
	for(int i = 0; i < TERRITORIES_N_AMERICA; ++i)
	{
		ter = new Territory(CONTINENT_ID_N_AMERICA);
		territoryNodes.add(ter);
	}
	for(int i = TERRITORIES_N_AMERICA; i < (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA); ++i)
	{
		ter = new Territory(CONTINENT_ID_S_AMERICA);
		territoryNodes.add(ter);
	}
	for(int i = (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA); i < (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE); ++i)
	{
		ter = new Territory(CONTINENT_ID_EUROPE);
		territoryNodes.add(ter);
	}
	for(int i = (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE); i < (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA); ++i)
	{
		ter = new Territory(CONTINENT_ID_AFRICA);
		territoryNodes.add(ter);
	}
	for(int i = (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA); i < (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA + TERRITORIES_ASIA); ++i)
	{
		ter = new Territory(CONTINENT_ID_ASIA);
		territoryNodes.add(ter);
	}
	for(int i = (TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA + TERRITORIES_ASIA); i < TERRITORIES_TOTAL; ++i)
	{
		ter = new Territory(CONTINENT_ID_OCEANIA);
		territoryNodes.add(ter);
	}

	for(int i = 0; i < territoryNodes.size(); ++i)
	{
		printf("i == %d, cont == %d, owner == %d\n", i, territoryNodes.get(i)->getContinent(), territoryNodes.get(i)->getOwner());
	}

	//North America
		//Alaska
	territoryNodes.get(0)->setArea(V2DF(80,550),30);
		//Alberta
	territoryNodes.get(1)->setArea(V2DF(165,505),20);
		//Central America
	territoryNodes.get(2)->setArea(V2DF(190,360),45);
		//Eastern United States
	territoryNodes.get(3)->setArea(V2DF(220,440),40);
		//Greenland
	territoryNodes.get(4)->setArea(V2DF(465,580),40);
		//Northwest Territory
	territoryNodes.get(5)->setArea(V2DF(215,565),30);
		//Ontario
	territoryNodes.get(6)->setArea(V2DF(245,505),25);
		//Quebec
	territoryNodes.get(7)->setArea(V2DF(310,500),40);
		//Western United States
	territoryNodes.get(8)->setArea(V2DF(140,450),40);

	//South America
	//Europe
	//Africa
	//Asia
	//Oceania
	printf("size == %d\n", territoryNodes.size());
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
	initTerritoryNodes();
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

	for(int i = 0; i < territoryNodes.size(); ++i)
		delete territoryNodes.get(i);

	return 0;
}
