#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <iostream>
#include "IArtificialIntelligence.hpp"

class Random : public IArtificialIntelligence
{
public:
	Random(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	Random(Random *);
	~Random() {}

	Random & operator=(Random *);

	virtual Action actualize(std::vector<AIPosition>&);

};

#endif //__BASIC_HPP__
