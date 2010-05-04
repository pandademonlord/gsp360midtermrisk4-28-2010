#pragma once

class Shape
{
protected:
	int c_r, c_g, c_b;
public:
	void setColor(int r, int g, int b)
	{
		c_r = r;	c_g = g;	c_b = b;
	}
};