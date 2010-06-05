#pragma once

#include "shape.h"
#include "v2d.h"
#include "random.h"
#include "line.h"

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
	bool isClockwise;
public:
	/**
	* @param a_point which point is being checked for being inside
	* @param a_clockwise if the points in this polygon are given in clockwise order
	* @return true if a_point is within the shape
	* @note contingent on a convex polygon, with the proper a_clockwise value supplied
	*/
	bool isInside(V2DF & a_point, bool a_clockwise)
	{
		bool oneIsDifferent = false;
		int numLines = 3;
		Line * line;
		//for(int i = 0; !oneIsDifferent && i < numLines; ++i)
		//{
			line = new Line(a,b);
			oneIsDifferent |= (line->isClockwise(a_point) == a_clockwise);
			line = new Line(b,c);
			oneIsDifferent |= (line->isClockwise(a_point) == a_clockwise);
			line = new Line(c,a);
			oneIsDifferent |= (line->isClockwise(a_point) == a_clockwise);
		//}
			return !oneIsDifferent;
	}
	/** @return the center of this polygon */
	V2DF getCenter()
	{
		V2DF center(0,0);
		for(int i = 0; i < 3; ++i)
		{
			center.add(getPoint(i));
			// center point, the average of all points
			center.divide(3);
		}
		return center;
	}
	Triangle(V2DF a_pt1, V2DF a_pt2, V2DF a_pt3)
	{
		this->a = a_pt1;
		this->b = a_pt2;
		this->c = a_pt3;
		this->isClockwise = isClockwiseCalc();
	}
	void glDraw()
	{
		glColor3ub(c_r, c_g, c_b);
		a.glDrawTo(b);
		b.glDrawTo(c);
		c.glDrawTo(a);
	}
	/** @return true if this polygon, if convex, has it's points in clockwise order */
	bool isClockwiseCalc()
	{
		return isInside(getCenter(), true);
	}
	bool isClickable(V2DF &click)
	{
		V2DF v0, m0;
		if(this->isClockwise)
		{
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
		else
		{
			v0 = b.difference(a);
			m0 = click.difference(a);
			if(v0.sign(m0) < 0)
				return false;

			v0 = c.difference(b);
			m0 = click.difference(b);
			if(v0.sign(m0) < 0)
				return false;

			v0 = a.difference(c);
			m0 = click.difference(c);
			if(v0.sign(m0) < 0)
				return false;

			return true;
		}
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
