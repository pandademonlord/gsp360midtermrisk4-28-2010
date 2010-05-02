#pragma once

#include "shape.h"
#include "v2d.h"
#include "drawing.h"
#include "random.h"

class Circle : public Shape
{
protected:
	V2DF center;
	float radius;
public:
	Circle(V2DF center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}
	Circle()
	{
		Circle(V2DF(0,0), 0);
	}
	void setCenter(V2DF a_center)
	{
		this->center = a_center;
	}
	void setRadius(float a_radius)
	{
		this->radius = a_radius;
	}
	void glDraw()
	{
		glColor3ub(c_r, c_g, c_b);
		glDrawCircle(center.getX(), center.getY(), radius);
	}
	bool isClickable(V2DF &click)
	{
		if(click.isWithin(radius, this->center))
			return true;
		else
			return false;
	}
	V2DF getCenter(){return center;}
	float getRadius(){return radius;}
};