#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include <math.h>
#include "IArtificialIntelligence.hpp"

class Circle : public IArtificialIntelligence
{
public:
	Circle(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	Circle(Circle *);
	~Circle() {}

	Circle & operator=(Circle *);

	virtual Action actualize(std::vector<AIPosition>&);

private:
	float 		_angle;
	float 		_rayon;
	AIPosition _center;
};

#endif
