#ifndef PLAYWORLD_H_
#define PLAYWORLD_H_

#include "AWorld.h"
#include "Components.h"

class PlayWorld : public ge::AWorld {
public:
	PlayWorld() = default;
	PlayWorld(PlayWorld const & other) = delete;
	PlayWorld(PlayWorld && other) = delete;
	~PlayWorld() override = default;

	PlayWorld & operator=(PlayWorld const & other) = delete;
	PlayWorld & operator=(PlayWorld && other) = delete;

	uint32_t CreatePlayer(ge::Component const & component, Position const & position, Velocity const & velocities, Sprite const & sprite);
	uint32_t CreateCross(ge::Component const & component, Position const & position, Sprite const & sprite);

	Sprite & Sprites(uint32_t id);
	Position & Positions(uint32_t id);
	Velocity & Velocities(uint32_t id);

private:
	std::array<Sprite, ge::Settings::EntitiesCount> sprites_{};
	std::array<Position, ge::Settings::EntitiesCount> positions_{};
	std::array<Velocity, ge::Settings::EntitiesCount> velocities_{};
};

#endif /* PLAYWORLD_H_ */
