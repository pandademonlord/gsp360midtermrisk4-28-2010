
/**
 * @param key what keyboard key was pressed (ASCII codes)
 * @param x/y where the mouse was at the time
 * @note: the following may be helpful:<code>
int state=glutGetModifiers();
if (state & GLUT_ACTIVE_SHIFT)	// shift is pressed</code>
 */
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case ' ':
		//printf("space was pressed\n");
		break;
	}
	glutPostRedisplay();
}

/** @param a_width/a_height new dimensions of the resized window */
void reshape(int a_width, int a_height)
{
	// have the graphics context calculate the changes...
	g_screen.reshape(a_width, a_height);
	// now, lets see it!
	glutPostRedisplay();
}

/** @param x/y the coordinate of where the mouse is being dragged */
void draggedMotion(int x, int y)
{
	//printf("mouse dragged (pixel location: %d, %d)\n",x,y);
}

/** @param x/y the coordinate of where the mouse is */
void passiveMotion(int x, int y)
{
	//printf("mouse moved (pixel location: %d, %d)\n",x,y);
	flags[FLAG_WITHIN_AREA] = false;
	static short prev_state = false;
	V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
	for(int i = 0; i < board.size(); ++i)
	{
		if(board.get(i)->isWithin(click))
		{
			flags[FLAG_WITHIN_AREA] = true;
			flags[FLAG_CLICKED_TER] = i;
			board.get(flags[FLAG_CLICKED_TER])->setColor(HIGHLIGHT_COLOR);
			break;
		}
		board.get(flags[FLAG_CLICKED_TER])->useContinentColor();
	}
	glutPostRedisplay();
	//printf("flags[FLAG_WITHIN_AREA] == %d, flags[FLAG_CLICKED_TER] == %d\n", flags[FLAG_WITHIN_AREA], flags[FLAG_CLICKED_TER]);
}

void mouse(int button, int state, int x, int y)
{
	//printf("button %d, state %d,  x %d, y %d\n", button, state, x, y);
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		switch(state)
		{
		case STATE_MOUSE_BUTTON_DN:
			if(flags[FLAG_WITHIN_AREA])
			{
				switch(flags[FLAG_GAME_STATE])
				{
				case STATE_INIT_PLACEMENT_CLAIM:
				case STATE_INIT_PLACEMENT_PLACE:
				case STATE_PLACE_BONUS_TROOPS:
					flags[FLAG_PARAM_ONE] = flags[FLAG_CLICKED_TER];
					flags[FLAG_PARAMS_SET] = true;
					break;
				}
				//printf("state == %d\n", flags[FLAG_GAME_STATE]);
			}
			else
			{
				switch(flags[FLAG_GAME_STATE])
				{
				case STATE_ATTACK:
				case STATE_FORTIFY:
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
			}
			break;
		}
		//V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
		//printf("clicked at cartiesian coordinate %f, %f\n", click.getX(), click.getY());
		break;
	case GLUT_RIGHT_BUTTON:
		/*switch(state)
		{
		case STATE_MOUSE_BUTTON_DN:
			break;
		}*/
		break;
	}
}
	

/** @return true if the game changed state and should redraw */
bool update(int a_ms)
{
	switch(flags[FLAG_GAME_STATE])
	{
	case STATE_INIT_PLACEMENT_CLAIM:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		for(int i = 0; i < board.size(); ++i)
		{
			if(board.get(i)->getOwner() == OWNER_NONE)
				flags[FLAG_UPDATE_GAME_STATE] = false;
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(board.get(flags[FLAG_PARAM_ONE])->getOwner() == OWNER_NONE)
			{
				players.get(flags[FLAG_CURRENT_PLAYER])->addLocal(board.get(flags[FLAG_PARAM_ONE]));
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_ONE]));
				flags[FLAG_UPDATE_PLAYER] = true;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_INIT_PLACEMENT_PLACE:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		for(int i = 0; i < players.size(); ++i)
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
				flags[FLAG_UPDATE_GAME_STATE] = false;
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(board.get(flags[FLAG_PARAM_ONE])->getOwner() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
			{
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_ONE]));
				flags[FLAG_UPDATE_PLAYER] = true;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_GET_TROOPS_TERRITORY:
		flags[FLAG_UPDATE_PLAYER] = false;
		flags[FLAG_UPDATE_GAME_STATE] = true;
		players.get(flags[FLAG_CURRENT_PLAYER])->Reinforcements(board);
		break;
	case STATE_GET_TROOPS_CARDS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_PLACE_BONUS_TROOPS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
			flags[FLAG_UPDATE_GAME_STATE] = false;
		if(flags[FLAG_PARAMS_SET])
		{
			if(board.get(flags[FLAG_PARAM_ONE])->getOwner() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_ONE]));
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_ATTACK:
		//flags[FLAG_UPDATE_GAME_STATE] = false;
		break;
	case STATE_FORTIFY:
		//flags[FLAG_UPDATE_GAME_STATE] = false;
		break;
	case STATE_WINNING:
		flags[FLAG_UPDATE_GAME_STATE] = false;
		break;
	}
	if(flags[FLAG_UPDATE_PLAYER])
	{
		flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] + 1;
		flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] % flags[FLAG_PLAYERS];
		flags[FLAG_UPDATE_PLAYER] = false;
	}
	//if(flags[FLAG_STATE_CUR_TURN_ENTER])
	//	flags[FLAG_STATE_CUR_TURN_ENTER] = false;
	if(flags[FLAG_UPDATE_GAME_STATE])
	{
		if(flags[FLAG_GAME_STATE] == STATE_INIT_PLACEMENT_PLACE)
			flags[FLAG_CURRENT_PLAYER] = PLAYER_ONE;
		if(flags[FLAG_GAME_STATE] == STATE_FORTIFY)
		{
			flags[FLAG_GAME_STATE] = STATE_GET_TROOPS_TERRITORY;
			flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] + 1;
			flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] % flags[FLAG_PLAYERS];
		}
		else
		{
			flags[FLAG_GAME_STATE] = flags[FLAG_GAME_STATE] + 1;
			flags[FLAG_GAME_STATE] = flags[FLAG_GAME_STATE] % STATES_TOTAL;
		}
		flags[FLAG_UPDATE_GAME_STATE] = false;
		flags[FLAG_STATE_CUR_TURN_ENTER] = true;
		printf("state == %d\n", flags[FLAG_GAME_STATE]);
		return true;
	}
	else
		return false;
}
