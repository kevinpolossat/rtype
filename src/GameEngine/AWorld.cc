#include "AWorld.h"

GameObject & ge::AWorld::Entities(uint32_t id) {
	return entities_[id];
}
