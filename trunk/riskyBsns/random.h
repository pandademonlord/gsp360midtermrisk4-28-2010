#pragma once

#include "v2d.h"

void seedRandom(const int & a_seed);

/**
 * custom random method to avoid reliance on stdlib.h
 * @return random (linear congruential) number between 0 and 32767
 */
int random();

/**
 * @param a_min the minimum possible value (inclusive)
 * @param a_max the maximum possible value (exclusive)
 * @return a random variable between [a_min and a_max)
 */
float randomFloat(const float & a_min, const float & a_max);

/** @return a randon floating-point value between [0 and 1) */
inline float randFloat(){return randomFloat(0, 1);}

/** @return a random V2D within a given range */
template <typename VTYPE>
inline V2D<VTYPE> randomV2D(const V2D<VTYPE> & a_min, const V2D<VTYPE> & a_max)
{
	return V2D<VTYPE>(
		(VTYPE)randomFloat(a_min.getX(), a_max.getX()),
		(VTYPE)randomFloat(a_min.getY(), a_max.getY()));
}