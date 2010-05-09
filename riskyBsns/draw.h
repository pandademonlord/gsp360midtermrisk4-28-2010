//#pragma once
#include "drawing.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	//glColor3f(COLOR_GREY);
	//g_screen.glDraw(DASH_SIZE);	// draw the cartisian plane in white

	//draw code
	char buffer[BUFFER_SIZE];
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->drawConnections();
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->glDraw();
	for(int i = 0; i < flags[FLAG_PLAYERS]; ++i)
	{
		players.get(i)->drawStats(board);
		if(flags[FLAG_CURRENT_PLAYER] == players.get(i)->getID())
		{
			switch(flags[FLAG_GAME_STATE])
			{
			case STATE_INIT_PLACEMENT_CLAIM:
				sprintf(buffer, "Player %d's turn: Claim a Territory\n", (players.get(i)->getID() + 1));
				break;
			case STATE_INIT_PLACEMENT_PLACE:
				sprintf(buffer, "Player %d's turn: Add 1 Army (%d Left)\n", (players.get(i)->getID() + 1), players.get(i)->getTroops());
				break;
			case STATE_GET_AND_PLACE_TROOPS:
				sprintf(buffer, "Player %d's turn: Deploy %d Troops\n", (players.get(i)->getID() + 1), players.get(i)->getTroops());
				break;
			/*case STATE_ATTACK:
				break;
			case STATE_FORTIFY:
				break;
			case STATE_WINNING:
				break;*/
			}
			(V2DF(0,0)).glDrawString(buffer);
		}
	}

	glFlush();			// print everything to the screen
	glutSwapBuffers();	// swap the draw buffers
}
