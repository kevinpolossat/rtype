#include "LoopTimer.h"

ge::LoopTimer::LoopTimer()
		: nextGameTick_(Clock::now()) {
}

void ge::LoopTimer::Start() {
	loops_ = 0;
}

bool ge::LoopTimer::Update() {
	bool ret = Clock::now() > nextGameTick_ && loops_ < maxFrameSkip;
	if (ret) {
		nextGameTick_ += std::chrono::milliseconds(msToSkip);
		++loops_;
	}
	return ret;
}

float ge::LoopTimer::GetInterpolation() const {
	return Duration(Clock::now() + Duration(msToSkip) - nextGameTick_) / Duration(msToSkip);
	;
}
