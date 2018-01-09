#include "AWorld.h"

uint32_t AWorld::GetEmptyIndex_() const {
	auto it = std::find(std::begin(entities_), std::end(entities_), component::none);
	return it != std::end(entities_) ? it - std::begin(entities_) : settings::ENTITY_COUNT;
}

void AWorld::Reset() {
	for (auto & entity : entities_) {
		entity = component::none;
	}
}

void AWorld::RemoveEntity(uint32_t const id) {
	entities_[id] = component::none;
}

Entity & AWorld::Entities(uint32_t id) {
	return entities_[id];
}
