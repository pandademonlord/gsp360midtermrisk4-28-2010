#include "random.h"

static const int g_MAX_RAND = 32767;

// our initial starting seed is 5323
static unsigned int nSeed = 5323;

void seedRandom(const int & a_seed)
{
	nSeed = a_seed;
}

/**
 * custom random method to avoid reliance on stdlib.h
 * @return random (linear congruential) number between 0 and 32767
 */
int random()
{
	// Take the current seed and generate a new value 
	// from it. Due to our use of large constants and 
	// overflow, it would be very hard for someone to
	// predict what the next number is going to be from 
	// the previous one.
	nSeed = (8253729 * nSeed + 2396403);
	// return a value between 0 and 32767
	return nSeed  % g_MAX_RAND;
}

float randomFloat(const float & a_min, const float & a_max)
{
	int randomInt = random();
	float range = a_max-a_min;
	float number = (float)randomInt * range / (float)g_MAX_RAND;
	number += a_min;
	return number;
}