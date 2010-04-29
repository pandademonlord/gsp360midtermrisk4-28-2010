#include <stdio.h>
#include "glut.h"
#include "random.h"
#include "v2d.h"

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1230,630);
	glutCreateWindow("Risk");
	glutDisplayFunc(display);
	glutMainLoop();
}
