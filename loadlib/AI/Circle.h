#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include <cmath>
#include "IArtificialIntelligence.hpp"

class Circle : public IArtificialIntelligence
{
public:
	explicit Circle(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Circle() {}

	virtual Action actualize(const uint32_t enX, const uint32_t enY);

private:
	float 		_angle;
	float 		_rayon;
	AIPosition _center;
};

#endif
