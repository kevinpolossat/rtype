#ifndef __SINUS_HPP__
#define __SINUS_HPP__

#include <cmath>
#include "IArtificialIntelligence.hpp"

class Sinus : public IArtificialIntelligence
{
public:
	explicit Sinus(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Sinus() {}

	virtual Action actualize(const uint32_t enX, const uint32_t enY);

private:
	float 			_angle;
	float 			_rayon;
	int 				_stockY;
};

#endif
