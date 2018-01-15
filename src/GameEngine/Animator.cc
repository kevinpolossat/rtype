#include "Animator.h"

void ge::Animator::AddAnimation(std::string const & name, ge::Animation const & animation) {
	animations_.insert(std::pair<std::string, Animation>(name, animation));
}

void ge::Animator::SetAnimation(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_ = std::stack<std::string>() ;
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

void ge::Animator::DoOnce(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

std::string ge::Animator::GetSprite() {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return "";
	}
	if (animations_.count(currents_.top())) {
		Animation & animation = animations_[currents_.top()];
		while (std::chrono::high_resolution_clock::now() > time_) {
			time_ += std::chrono::milliseconds(animation.speed);
			if (animation.current + 1 >= animation.sprites.size()) {
				animation.current = 0;
				if (currents_.size() > 1) {
					currents_.pop();
				}
			} else {
				++animation.current;
			}
		}
		return animation.sprites[animation.current];
	} else {
		ErrorUnknownAnimation_("currents_");
		return "";
	}
}

int32_t ge::Animator::GetPriority() const {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return 0;
	}
	if (animations_.count(currents_.top())) {
		return animations_.at(currents_.top()).priority;
	} else {
		ErrorUnknownAnimation_(currents_.top());
		return 0;
	}
}

void ge::Animator::ErrorUnknownAnimation_(std::string const & name) const {
	std::cerr << "Animator : Animation " << name << " doesn't exist" << std::endl;
}

void ge::Animator::ErrorNoAnimation_() const {
	std::cerr << "Animator : No animation set" << std::endl;
}

ge::Animator::AnimationsList const & ge::Animator::GetAnimationsList() const {
	return animations_;
}
