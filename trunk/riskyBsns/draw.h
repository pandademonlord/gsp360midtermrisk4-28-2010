//#pragma once
#include "drawing.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glColor3f(COLOR_GREY);
	g_screen.glDraw(DASH_SIZE);	// draw the cartisian plane in white

	//draw code
	//for(int i = 0; i < territoryNodes.size(); ++i)
	for(int i = 0; i < TERRITORIES_N_AMERICA; ++i)
	{
		territoryNodes.get(i)->glDraw();
	}

	glFlush();			// print everything to the screen
	glutSwapBuffers();	// swap the draw buffers
}
