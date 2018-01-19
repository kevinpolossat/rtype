#ifndef __BASIC_HPP__
#define __BASIC_HPP__

#include "IArtificialIntelligence.hpp"

class Basic : public IArtificialIntelligence
{
public:
	explicit Basic(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Basic() {}

	virtual Action actualize(const uint32_t enX, const uint32_t enY);

};

#endif //__BASIC_HPP__
