#ifndef __SINUS_HPP__
#define __SINUS_HPP__

#include <math.h>
#include "IArtificialIntelligence.hpp"

class Sinus : public IArtificialIntelligence
{
public:
	Sinus(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	Sinus(Sinus *);
	~Sinus() {}

	Sinus & operator=(Sinus *);

	virtual Action actualize(std::vector<AIPosition>&);

private:
	float 			_angle;
	float 			_rayon;
	int 				_stockY;
};

#endif
