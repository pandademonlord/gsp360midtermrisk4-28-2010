//#pragma once
#include "drawing.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glColor3f(COLOR_GREY);
	g_screen.glDraw(DASH_SIZE);	// draw the cartisian plane in white

	//draw code
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->drawConnections();
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->glDraw();

	glFlush();			// print everything to the screen
	glutSwapBuffers();	// swap the draw buffers
}
