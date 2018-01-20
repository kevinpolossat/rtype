#ifndef __BASIC_HPP__
#define __BASIC_HPP__

#include "IArtificialIntelligence.hpp"

class Basic : public IArtificialIntelligence
{
public:
	Basic(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	Basic(Basic *);
	~Basic() {}

	Basic & operator=(Basic *);

	virtual Action actualize(std::vector<AIPosition>&);

};

#endif //__BASIC_HPP__
