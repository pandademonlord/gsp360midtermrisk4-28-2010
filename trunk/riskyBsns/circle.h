#pragma once

#include "shape.h"
#include "v2d.h"
#include "drawing.h"

class Circle : public Shape
{
private:
	V2DF center;
	float radius;
public:
	Circle(V2DF a_center, float a_radius)
	{
		this->center = a_center;
		this->radius = a_radius;
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
		glDrawCircle(this->center.getX(), this->center.getY(), this->radius);
	}
	bool isClickable(V2DF &click)
	{
		return click.isWithin(this->radius, this->center);
	}
	V2DF getCenter(){return center;}
	float getRadius(){return radius;}
};