#ifndef LOOP_TIMER_H
#define LOOP_TIMER_H

#include <chrono>

namespace ge {
	static constexpr uint32_t updatePerSecond = 25;
	static constexpr uint32_t msToSkip = 1000 / updatePerSecond;
	static constexpr uint32_t maxFrameSkip = 5;

	class LoopTimer {
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using Duration = std::chrono::duration<float, std::milli>;

	public:
		LoopTimer();
		LoopTimer(LoopTimer const & other) = delete;
		LoopTimer(LoopTimer && other) = delete;
		~LoopTimer() = default;

		LoopTimer & operator=(LoopTimer const & other) = delete;
		LoopTimer & operator=(LoopTimer && other) = delete;

		void Start();
		bool Update();
		float GetInterpolation() const;

	private:
		uint32_t loops_;
		TimePoint nextGameTick_;
	};
}

#endif /*LOOP_TIMER_H*/
