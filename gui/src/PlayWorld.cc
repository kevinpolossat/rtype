#include "PlayWorld.h"

uint32_t PlayWorld::CreatePlayer(Position const & position, Velocity const & velocities) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component::player;
	positions_[id] = position;
	velocities_[id] = velocities;
	return id;
}

Position & PlayWorld::Positions(uint32_t id) {
	return positions_[id];
}

Velocity & PlayWorld::Velocities(uint32_t id) {
	return velocities_[id];
}