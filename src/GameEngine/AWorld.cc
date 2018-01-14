#include "AWorld.h"

uint32_t ge::AWorld::GetEmptyIndex_() const {
	auto it = std::find(std::begin(entities_), std::end(entities_), ge::Components::None);
	return it != std::end(entities_) ? static_cast<uint32_t >(it - std::begin(entities_)) : ge::Settings::EntitiesCount;
}

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
