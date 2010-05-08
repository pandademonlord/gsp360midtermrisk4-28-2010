
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
					case STATE_INIT_PLACEMENT:
						flags[FLAG_PARAM_ONE] = flags[FLAG_CLICKED_TER];
						flags[FLAG_PARAMS_SET] = true;
						break;
				}
				printf("state == %d\n", flags[FLAG_GAME_STATE]);
			}
			break;
		}
		//V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
		//printf("clicked at cartiesian coordinate %f, %f\n", click.getX(), click.getY());
		break;
	}
	//glutPostRedisplay();
}

/** @return true if the game changed state and should redraw */
bool update(int a_ms)
{
	switch(flags[FLAG_GAME_STATE])
	{
		case STATE_INIT_PLACEMENT:
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
					players.get(flags[FLAG_CURRENT_PLAYER])->addlocal(board.get(flags[FLAG_PARAM_ONE]));
					players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_ONE]));
				}
				flags[FLAG_PARAMS_SET] = false;
				flags[FLAG_UPDATE_PLAYER] = true;
			}
			break;
		/*case STATE_GET_AND_PLACE_TROOPS:
			break;
		case STATE_ATTACK:
			break;
		case STATE_FORTIFY:
			break;
		case STATE_WINNING:
			break;*/
	}
	if(flags[FLAG_UPDATE_PLAYER])
	{
		flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] + 1;
		flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] % flags[FLAG_PLAYERS];
		flags[FLAG_UPDATE_PLAYER] = false;
	}
	if(flags[FLAG_UPDATE_GAME_STATE])
	{
		flags[FLAG_GAME_STATE] = flags[FLAG_GAME_STATE] + 1;
		flags[FLAG_GAME_STATE] = flags[FLAG_GAME_STATE] % STATES_TOTAL;
		flags[FLAG_UPDATE_GAME_STATE] = false;
		return true;
	}
	else
		return false;
}
