#include <stdio.h>	// for printf()
#include <time.h>	// for clock()

#include "GLUTRenderingContext.h"
#include "random.h"

#define SCREEN_HEIGHT			630
#define SCREEN_WIDTH			1230
#define SCREEN_MAX_X			SCREEN_WIDTH
#define SCREEN_MAX_Y			SCREEN_HEIGHT
#define SCREEN_MIN_X			0
#define SCREEN_MIN_Y			0
#define COLOR_GREY				.5,.5,.5
#define INIT_WINDOW_X			10
#define INIT_WINDOW_Y			50
#define TIMER_VALUE				20

#include "templatearray.h"
#include "templatevector.h"
#include "draw.h"
#include "eventhandlers.h"

GLUTRenderingContext g_screen(V2DF(SCREEN_WIDTH,SCREEN_HEIGHT), V2DF(SCREEN_MIN_X,SCREEN_MIN_Y), V2DF(SCREEN_MAX_X,SCREEN_MAX_Y));

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
	g_screen.glSetupScreen();
	glutInitWindowPosition(INIT_WINDOW_X,INIT_WINDOW_Y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Risk");
    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(draggedMotion);
	glutMouseFunc(mouse);
}

int main(int argc, char **argv) {
	seedRandom(time(NULL));
	glutInit(&argc, argv);
	init();
	glutTimerFunc(0, updateTimerFunction, TIMER_VALUE);
    glutMainLoop();
	return 0;
}