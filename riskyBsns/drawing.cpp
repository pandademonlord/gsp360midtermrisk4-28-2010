#define ARC_SEGMENTS	6
#define ARC_NODES		(ARC_SEGMENTS+1)

#include "V2D.h"

float g_lastRadius = -1;
V2DF g_arc[ARC_NODES];
// must result in a normalized (unit-vector) value
V2DF g_normal(V2D_HALFPI/ARC_SEGMENTS);

bool glDrawCircle(const float & x, const float & y, const float & a_radius)
{
	// recalculate the points of a quarter-circle if needed
	if(g_lastRadius != a_radius)
	{
		g_arc[0].set(1, 0);
		V2DF * lastPoint;
		// calculate all points in the arc as normals
		for(int i = 1; i < ARC_NODES; ++i)
		{
			// faster memory reference than g_arc[i-1]
			lastPoint = &g_arc[i-1];
			// calculate turn in next point
			g_arc[i].set(
				// x_ = x*cos(theta) - y*sin(theta)
				lastPoint->getX()*g_normal.getX() - lastPoint->getY()*g_normal.getY(), 
				// y_ = x*sin(theta) + y*cos(theta)
				lastPoint->getX()*g_normal.getY() + lastPoint->getY()*g_normal.getX());
		}
		// put length data back into normalized vector
		for(int i = 0; i < ARC_NODES; ++i)
		{
			// embarassingly parallel
			g_arc[i].multiply(a_radius);
		}
		// don't recalculate a circle for this radius next time...
		g_lastRadius = a_radius;
	}
	glPushMatrix();
	glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)0);
	glBegin(GL_LINE_STRIP);
	int i, lastSegment = ARC_NODES-1;
	// draw top-right
	for(i = 0; i < ARC_NODES; ++i)	g_arc[i].glVertex();
	// flip horizontally
	for(i = lastSegment; i >= 0; --i)	g_arc[i].flipAxis(g_arc[i].X);
	// draw top-left
	for(i = lastSegment; i >= 0; --i)	g_arc[i].glVertex();
	// flip vertically
	for(i = lastSegment; i >= 0; --i)	g_arc[i].flipAxis(g_arc[i].Y);
	// draw bottom-left
	for(i = 0; i < ARC_NODES; ++i)	g_arc[i].glVertex();
	// flip horizontally
	for(i = lastSegment; i >= 0; --i)	g_arc[i].flipAxis(g_arc[i].X);
	// draw bottom-right
	for(i = lastSegment; i >= 0; --i)	g_arc[i].glVertex();
	glEnd();
	glPopMatrix();
	return true;
}
