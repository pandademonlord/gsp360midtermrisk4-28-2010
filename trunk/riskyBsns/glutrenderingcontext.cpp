#include "glutrenderingcontext.h"

/** sets up the openGL screen according to current variables */
void GLUTRenderingContext::glSetupScreen()
{
	// re-define the window size
	glutInitWindowSize(dimensionPixels.getX(),dimensionPixels.getY());
	// reset The Current Viewport
	glViewport(0,0,(int)dimensionPixels.getX(),(int)dimensionPixels.getY());
}

/** sets up the cartesian plane for openGL/GLUT */
void GLUTRenderingContext::ortho2D()
{
	// reset the view matrix
	glLoadIdentity();
	// set the view matrix to match this context
	gluOrtho2D(minX(), maxX(), minY(), maxY());
}

/** 
 * @param a_position x/y in pixels (like from a mouse press) 
 * @return cartesian coordinate equivalent
 */
V2DF GLUTRenderingContext::convertPixelsToCartesian(const V2DF & a_position) const
{
	V2DF dim = getDimension();
	// because the y axis is inverted...
	V2DF pos(a_position.getX(), dimensionPixels.getY()-a_position.getY());
	V2DF cartesian = pos.product(dim);
	cartesian.divide(dimensionPixels);
	cartesian.add(getMin());
	return cartesian;
}

/**
 * resizes the image for the cartesian plane
 */
void GLUTRenderingContext::reshape(int a_widthPixels, int a_heightPixels)
{
	// figure out percentage change of new size vs old size (in pixels)
	V2DF newDimension(a_widthPixels, a_heightPixels);
	V2DF changePercent = newDimension.quotient(dimensionPixels);
	dimensionPixels = newDimension;
	// will use dimensionPixels to setup the screen
	glSetupScreen();
	V2DF dimension(getDimension());
	// multiply the cartesian system by the change in the pixel system
	dimension.multiply(changePercent);
	setDimension(dimension);
	// reset the display
	ortho2D();
}

/**
 * draw the cartesian plane 
 * @param a_dashSize how big to make the unit marks (sample value: 0.1)
 */
void GLUTRenderingContext::glDraw(float a_dashSize)
{
	glBegin(GL_LINES);
	glVertex2f(0, maxY());	V2DF::ZERO().glVertex();
	glVertex2f(0, minY());	V2DF::ZERO().glVertex();
	glVertex2f(minX(), 0);	V2DF::ZERO().glVertex();
	glVertex2f(maxX(), 0);	V2DF::ZERO().glVertex();
	if(a_dashSize > 0)
	{
		int i;
		for(i = 1; i < maxY(); i++)	{glVertex2f(-0.1, i);	glVertex2f(0.1, i);}
		for(i =-1; i > minY(); i--)	{glVertex2f(-0.1, i);	glVertex2f(0.1, i);}
		for(i = 1; i < maxX(); i++)	{glVertex2f(i, -0.1);	glVertex2f(i, 0.1);}
		for(i =-1; i > minX(); i--)	{glVertex2f(i, -0.1);	glVertex2f(i, 0.1);}
	}
	glEnd();
}
