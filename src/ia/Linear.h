#ifndef __LINEAR_HPP__
#define __LINEAR_HPP__

#include "IArtificialIntelligence.hpp"

class Linear : public IArtificialIntelligence
{
public:
	Linear(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	Linear(Linear *);
	~Linear() {}

	Linear & operator=(Linear *);

	virtual Action actualize(std::vector<AIPosition>&);

private:
	int _x;

};

#endif
