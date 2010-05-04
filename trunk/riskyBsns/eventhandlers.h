
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
	//for(int i = 0; i < territoryNodes.size(); ++i)
	for(int i = 0; i < TERRITORIES_N_AMERICA; ++i)
	{
		if(territoryNodes.get(i)->isWithin(click))
		{
			flags[FLAG_WITHIN_AREA] = true;
			flags[FLAG_CLICKED_TER] = i;
			break;
		}
	}
	if(flags[FLAG_WITHIN_AREA])
		territoryNodes.get(flags[FLAG_CLICKED_TER])->setColor(WITHIN_TER_Y);
	else
		territoryNodes.get(flags[FLAG_CLICKED_TER])->setColor(WITHIN_TER_N);
	if(prev_state != flags[FLAG_WITHIN_AREA])
	{	
		prev_state = flags[FLAG_WITHIN_AREA];
		glutPostRedisplay();
	}
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
				printf("clicked territory #%d\n", flags[FLAG_CLICKED_TER]);
			break;
		case STATE_MOUSE_BUTTON_UP:
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
	return false;
}
