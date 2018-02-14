#ifndef RTYPE_RANDOMGENERATOR_H
#define RTYPE_RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
public:
	~RandomGenerator() = default;

	static uint32_t Rand();

	RandomGenerator(RandomGenerator const &) = delete;
	RandomGenerator(RandomGenerator &&) = delete;
	RandomGenerator & operator = (RandomGenerator const &) = delete;
	RandomGenerator & operator = (RandomGenerator &&) = delete;

private:
	RandomGenerator();

	std::mt19937 mt_;
	std::uniform_real_distribution<float> dist_;
};

#endif //RTYPE_RANDOMGENERATOR_H
