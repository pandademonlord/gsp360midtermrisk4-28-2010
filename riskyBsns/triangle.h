#pragma once

#include "shape.h"
#include "v2d.h"
#include "random.h"

class Triangle : public Shape
{
protected:
	V2DF a, b, c;
	//starting at point A, and go clockwise to B and C
	//      *B
	//     / \
	//    /   \
	//   /     \
	// A*-------*C
public:
	Triangle(V2DF a_pt1, V2DF a_pt2, V2DF a_pt3)
	{
		this->a = a_pt1;
		this->b = a_pt2;
		this->c = a_pt3;
	}
	void glDraw()
	{
		glColor3ub(c_r, c_g, c_b);
		//glColor3ub(255, 0, 0);
		a.glDrawTo(b);
		//glColor3ub(0, 255, 0);
		b.glDrawTo(c);
		//glColor3ub(0, 0, 255);
		c.glDrawTo(a);
	}
	bool isClickable(V2DF &click)
	{
		V2DF v0, m0;

		v0 = b.difference(a);
		m0 = click.difference(a);
		if(v0.sign(m0) > 0)
			return false;

		v0 = c.difference(b);
		m0 = click.difference(b);
		if(v0.sign(m0) > 0)
			return false;

		v0 = a.difference(c);
		m0 = click.difference(c);
		if(v0.sign(m0) > 0)
			return false;

		return true;
	}
	void moveShape(const V2DF &delta)
	{
		a.add(delta);
		b.add(delta);
		c.add(delta);
	}
	V2DF getPoint(int get)
	{
		switch(get)
		{
		case 1:
			return b;
		case 2:
			return c;
		default:
			return a;
		}
	}
	bool collidesWithTriangle(Triangle * tri)
	{
		V2DF point;
		float dist;
		for(int i = 0; i < 3; ++i)
		{
			if((tri->isClickable(this->getPoint(i))) || (this->isClickable(tri->getPoint(i))))
				return true;
		}
		for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				if(point.lineIntersection(this->getPoint(i), this->getPoint(i+1), tri->getPoint(j), tri->getPoint(j+1), dist, point))
					return true;
			}
		}
		return false;
	}
};
