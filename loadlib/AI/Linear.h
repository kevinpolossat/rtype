#ifndef __LINEAR_HPP__
#define __LINEAR_HPP__

#include "IArtificialIntelligence.hpp"

class Linear : public IArtificialIntelligence
{
public:
	explicit Linear(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Linear() {}

	virtual Action actualize(const uint32_t enX, const uint32_t enY);

private:
	int _x;

};

#endif
