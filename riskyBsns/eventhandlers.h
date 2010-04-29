
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
		printf("space was pressed\n");
		break;
	}
	glutPostRedisplay();
}

/** @param x/y the coordinate of where the mouse is */
void passiveMotion(int x, int y)
{
	//printf("mouse moved (pixel location: %d, %d)\n",x,y);
}

/** @param x/y the coordinate of where the mouse is being dragged */
void draggedMotion(int x, int y)
{
	//printf("mouse dragged (pixel location: %d, %d)\n",x,y);
}

void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
	}
	glutPostRedisplay();
}

/** @return true if the game changed state and should redraw */
bool update(int a_ms)
{
	return false;
}
