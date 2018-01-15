#include "Animator.h"

void ge::Animator::AddAnimation(std::string const & name, ge::Animation const & animation) {
	animations_.insert(std::pair<std::string, Animation>(name, animation));
}

void ge::Animator::SetCurrentAnimation(std::string const & name) {
	if (name != current_) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		current_ = name;
		time_ = std::chrono::high_resolution_clock::now();
	}
}

std::string ge::Animator::GetSprite() {
	if (animations_.count(current_)) {
		Animation & animation = animations_[current_];
		while (std::chrono::high_resolution_clock::now() > time_) {
			time_ += std::chrono::milliseconds(animation.speed);
			if (animation.current + 1 >= animation.sprites.size()) {
				animation.current = 0;
			} else {
				++animation.current;
			}
		}
		return animation.sprites[animation.current];
	} else {
		ErrorUnknownAnimation_("current_");
		return "";
	}
}

int32_t ge::Animator::GetPriority() const {
	if (animations_.count(current_)) {
		return animations_.at(current_).priority;
	} else {
		ErrorUnknownAnimation_(current_);
		return 0;
	}
}

void ge::Animator::ErrorUnknownAnimation_(std::string const & name) const {
	std::cerr << "Animator : Animation " << name << " doesn't exist" << std::endl;
}

ge::Animator::AnimationsList const & ge::Animator::GetAnimationsList() const {
	return animations_;
}
