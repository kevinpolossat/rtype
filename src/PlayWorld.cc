#include "PlayWorld.h"

uint32_t PlayWorld::CreatePlayer(ge::Component const & component, Position const & position, Velocity const & velocities) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component;
	positions_[id] = position;
	velocities_[id] = velocities;
	ge::Animation walk;
	walk.priority = 1;
	for (uint32_t i = 1; i <= 10; ++i) {
		walk.sprites.push_back("resources/knight/Walk (" + std::to_string(i) + ").png");
	}
	ge::Animation attack;
	attack.priority = 1;
	for (uint32_t i = 1; i <= 10; ++i) {
		attack.sprites.push_back("resources/knight/Attack (" + std::to_string(i) + ").png");
	}
	animators_[id].AddAnimation("Walk", walk);
	animators_[id].AddAnimation("Attack", attack);
	animators_[id].SetCurrentAnimation("Walk");
	return id;
}

uint32_t PlayWorld::CreateCross(ge::Component const & component, Position const &position, Sprite const & sprite) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component;
	positions_[id] = position;
	sprites_[id] = sprite;
	return id;
}

Sprite &PlayWorld::Sprites(uint32_t id) {
	return sprites_[id];
}

Position & PlayWorld::Positions(uint32_t id) {
	return positions_[id];
}

Velocity & PlayWorld::Velocities(uint32_t id) {
	return velocities_[id];
}

ge::Animator & PlayWorld::Animators(uint32_t id) {
	return animators_[id];
}
