#include "glut.h"
#include "v2d.h"

/**
 * handles data & methods related to screen size and cartesian formatting
 * @author mvaganov@hotmail.com December 2009
 */
struct GLUTRenderingContext
{
	/** how many pixels wide and tall the screen is */
	V2DF dimensionPixels;
	/** the values at the edges of the cartesian plane */
	V2DF min, max;

	inline GLUTRenderingContext(const V2DF & a_dimensionPixels, 
		const V2DF & a_min, const V2DF & a_max)
		:dimensionPixels(a_dimensionPixels),min(a_min),max(a_max)
	{}

	inline float minX() const	{	return min.getX();	}
	inline float maxX() const	{	return max.getX();	}
	inline float minY() const	{	return min.getY();	}
	inline float maxY() const	{	return max.getY();	}

	inline V2DF getMin()const{return V2DF(minX(), minY());}
	inline V2DF getMax()const{return V2DF(maxX(), maxY());}
	inline V2DF getDimension()const{return max.difference(min);}
	inline void setDimension(const V2DF & a_dimension){max=min.sum(a_dimension);}


	/** sets up the openGL screen according to current variables */
	void glSetupScreen();

	/** sets up the cartesian plane for openGL/GLUT */
	void ortho2D();

	/** 
	 * @param a_position x/y in pixels (like from a mouse press) 
	 * @return cartesian coordinate equivalent
	 */
	V2DF convertPixelsToCartesian(const V2DF & a_position) const;

	/**
	 * resizes the image for the cartesian plane
	 */
	void reshape(int a_widthPixels, int a_heightPixels);

	/**
	 * draw the cartesian plane 
	 * @param a_dashSize how big to make the unit marks (sample value: 0.1)
	 */
	void glDraw(float a_dashSize);
};
