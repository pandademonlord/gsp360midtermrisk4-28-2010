//#pragma once
#include "drawing.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen

	//draw territories (connections, triangles, circle)
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->drawConnections();
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->glDrawWorld();
	for(int i = 0; i < board.size(); ++i)
		board.get(i)->glDraw();

	//draw buttons (rect, label)
	char buffer[BUFFER_SIZE];
	switch(flags[FLAG_GAME_STATE])
	{
		case STATE_ATTACK_FROM:
			buttons.get(BUTTON_GENERAL)->glDraw();
			sprintf(buffer, "END Attack\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_GENERAL)->getW())/4,5)))).glDrawString(buffer);
			break;
		case STATE_ATTACK_TO:
			buttons.get(BUTTON_GENERAL)->glDraw();
			sprintf(buffer, "Re-Select\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_GENERAL)->getW())/4,5)))).glDrawString(buffer);
			sprintf(buffer, "Attacking Territory\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().difference(V2DF(45,5)))).glDrawString(buffer);
			break;
		case STATE_FORTIFY_FROM:
			buttons.get(BUTTON_GENERAL)->glDraw();
			sprintf(buffer, "END Turn\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_GENERAL)->getW())/4,5)))).glDrawString(buffer);
			break;
		case STATE_FORTIFY_TO:
			buttons.get(BUTTON_GENERAL)->glDraw();
			sprintf(buffer, "Re-Select\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_GENERAL)->getW())/4,5)))).glDrawString(buffer);
			sprintf(buffer, "Fortifying Territory\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().difference(V2DF(45,5)))).glDrawString(buffer);
			break;
		case STATE_FORTIFY_TROOPS:
			for(int i = 0; i < buttons.size(); ++i)
				buttons.get(i)->glDraw();
			sprintf(buffer, "Move Troops\n");
			(V2DF(buttons.get(BUTTON_GENERAL)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_GENERAL)->getW())/4,5)))).glDrawString(buffer);
			sprintf(buffer, "Increase Troops\n");
			(V2DF(buttons.get(BUTTON_MOVE_INC)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_MOVE_INC)->getW())/3,5)))).glDrawString(buffer);
			sprintf(buffer, "Decrease Troops\n");
			(V2DF(buttons.get(BUTTON_MOVE_DEC)->getCenter().sum(V2DF(-1 * (buttons.get(BUTTON_MOVE_DEC)->getW())/3,5)))).glDrawString(buffer);
			break;
	}

	//draw user directions
	for(int i = 0; i < flags[FLAG_PLAYERS]; ++i)
	{
		players.get(i)->drawStats(board);
		if(flags[FLAG_CURRENT_PLAYER] == players.get(i)->getID())
		{
			switch(flags[FLAG_GAME_STATE])
			{
			case STATE_INIT_PLACEMENT_CLAIM:
				sprintf(buffer, "Click on Unoccupied Territory.\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Claim a Territory\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_INIT_PLACEMENT_PLACE:
				sprintf(buffer, "Click on Your Territory.\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Add 1 Army (%d Left)\n", (players.get(i)->getID() + 1), players.get(i)->getTroops());
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_PLACE_BONUS_TROOPS:
			case STATE_PLACE_EXCESS_TROOPS:
				sprintf(buffer, "Click on Your Territory.\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Deploy %d Troops\n", (players.get(i)->getID() + 1), players.get(i)->getTroops());
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_ATTACK_FROM:
				sprintf(buffer, "Click on Your Territory (2+ troops, Adjacent to Enemy).\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Attack (From Where?)\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_ATTACK_TO:
				sprintf(buffer, "Click on Enemy Territory (Adjacent to You).\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Attack (To Where?)\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_FORTIFY_FROM:
				sprintf(buffer, "Click on Your Territory (2+ troops, Adjacent to You).\n");
				sprintf(buffer, "Player %d's turn: Fortify (From Where?)\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_FORTIFY_TO:
				sprintf(buffer, "Click on Your Territory (Adjacent to You).\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Fortify (To Where?)\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_FORTIFY_TROOPS:
				sprintf(buffer, "Click Increase/Decrease Buttons.\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d's turn: Fortify (Moving %d Troops)\n", (players.get(i)->getID() + 1), flags[FLAG_PARAM_NUM]);
				(V2DF(0,5)).glDrawString(buffer);
				break;
			case STATE_WIN:
				sprintf(buffer, "GAME OVER\n");
				(V2DF(0,20)).glDrawString(buffer);
				sprintf(buffer, "Player %d WINS!\n", (players.get(i)->getID() + 1));
				(V2DF(0,5)).glDrawString(buffer);
				break;
			}
		}
	}

	glFlush();			// print everything to the screen
	glutSwapBuffers();	// swap the draw buffers
}
