#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

namespace ge {
	struct Animation {
		std::vector<std::string> sprites;
		uint32_t current = 0;
		uint32_t speed = 50;
		int32_t priority;
	};

	class Animator {
		using AnimationsList = std::unordered_map<std::string, Animation>;

	public:
		Animator() = default;
		Animator(Animator const & other) = delete;
		Animator(Animator && other) = delete;
		~Animator() = default;

		Animator & operator=(Animator const & other) = delete;
		Animator & operator=(Animator && other) = delete;

		void AddAnimation(std::string const & name, Animation const & animation);
		void SetCurrentAnimation(std::string const & name);

		std::string GetSprite();
		int32_t GetPriority() const;

		AnimationsList const & GetAnimationsList() const;

	private:
		void ErrorUnknownAnimation_(std::string const & name) const;

		std::chrono::time_point<std::chrono::high_resolution_clock> time_;
		std::string current_;
		AnimationsList animations_;
	};
}

#endif /*ANIMATOR_H*/
