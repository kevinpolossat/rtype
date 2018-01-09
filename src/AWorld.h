#ifndef AWORLD_H_
#define AWORLD_H_

#include <bitset>
#include <array>
#include <SFML/Graphics.hpp>
#include "Components.h"

class AWorld {
public:
	AWorld() = default;
	AWorld(AWorld const & other) = delete;
	AWorld(AWorld const && other) = delete;
	virtual ~AWorld() = default;

	AWorld & operator=(AWorld const & other) = delete;
	AWorld & operator=(AWorld const && other) = delete;

	void Reset();
	void RemoveEntity(uint32_t id);

	Entity & Entities(uint32_t id);

protected:
	virtual uint32_t GetEmptyIndex_() const;

	std::array<Entity, settings::ENTITY_COUNT> entities_;
};

#endif /* AWORLD_H_ */