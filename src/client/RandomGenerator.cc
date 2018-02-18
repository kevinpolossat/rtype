#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
		: mt_(std::random_device()()), dist_(0, 35000) {
}

uint32_t RandomGenerator::Rand() {
	static RandomGenerator impl_;

	return static_cast<uint32_t >(impl_.dist_(impl_.mt_));
}