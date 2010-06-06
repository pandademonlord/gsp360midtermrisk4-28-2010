#pragma once

#include "shape.h"
#include "v2d.h"

class Rect : public Shape
{
protected:
	V2DF a, c;
	float w, h;
public:
	Rect(V2DF a_a, V2DF a_c)
	{
		a = a_a;
		c = a_c;
	}
	Rect(V2DF a_point, float a_width, float a_height)
	{
		a = a_point;
		c = a_point.sum(V2DF(a_width, a_height));
		w = a_width;
		h = a_height;
	}
	float getW(){return w;}
	V2DF getCenter()
	{
		return V2DF((a.getX() + c.getX())/2, (a.getY() + c.getY())/2);
	}
	void glDraw()
	{
		glColor3ub(c_r, c_g, c_b);
		V2DF b = V2DF(c.getX(),a.getY());
		V2DF d = V2DF(a.getX(),c.getY());
		a.glDrawTo(b);
		b.glDrawTo(c);
		c.glDrawTo(d);
		d.glDrawTo(a);
	}
	bool isClickable(V2DF &click)
	{
		if(click.isBetweenRect(this->a, this->c))
			return true;
		else
			return false;
	}
	void moveShape(const V2DF &delta)
	{
		a.add(delta);
		c.add(delta);
	}
};
