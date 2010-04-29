void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glColor3f(COLOR_GREY);

	glFlush();			// print everything to the screen
	glutSwapBuffers();	// swap the draw buffers
}
