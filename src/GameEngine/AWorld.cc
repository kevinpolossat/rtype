#include "AWorld.h"

void ge::AWorld::Reset() {
	for (auto & entity : entities_) {
		entity = ge::Components::None;
	}
}

void ge::AWorld::RemoveEntity(uint32_t const id) {
	entities_[id] = ge::Components::None;
}

ge::Entity & ge::AWorld::Entities(uint32_t id) {
	return entities_[id];
}
