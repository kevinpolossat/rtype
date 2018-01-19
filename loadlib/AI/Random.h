#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <iostream>
#include "IArtificialIntelligence.hpp"

class Random : public IArtificialIntelligence
{
public:
	explicit Random(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Random() {}

	virtual Action actualize(const uint32_t enX, const uint32_t enY);

};

#endif //__BASIC_HPP__
