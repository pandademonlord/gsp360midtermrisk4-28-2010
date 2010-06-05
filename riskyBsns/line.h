#pragma once

class Line
{
protected:
	V2D<float> a, b;
public:
	V2D<float> getPosition(){return a;}
	void setPosition(V2D<float> & a_position)
	{
		V2D<float> d = b.difference(a);
		a.set(a_position);
		b.set(a_position.sum(d));
	}
	V2D<float> getA(){return a;}
	V2D<float> getB(){return b;}
	Line(){}
	void set(V2D<float> & a_a, V2D<float> & a_b)
		{a=a_a;b=a_b;}
	Line(V2D<float> & a_a, V2D<float> & a_b)
		{set(a_a,a_b);}
	void glDraw(){a.glDrawTo(b);}
	bool isClockwise( V2D<float> & a_point)
	{
		// use the first point as the anchor point
		V2D<float> b0 = b.difference(a),
		p0 = a_point.difference(a);
		return b0.sign(p0) > 0;
	}
	V2D<float> getCenter(){return a.sum(b).quotient(2);}
	bool contains(V2D<float> & a_point)
		{return a.equals(a_point) || b.equals(a_point);}
}; 