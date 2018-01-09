#ifndef PLAYWORLD_H_
#define PLAYWORLD_H_

#include "AWorld.h"

class PlayWorld : public AWorld {
public:
	PlayWorld() = default;
	PlayWorld(PlayWorld const & other) = delete;
	PlayWorld(PlayWorld const && other) = delete;
	~PlayWorld() override = default;

	PlayWorld & operator=(PlayWorld const & other) = delete;
	PlayWorld & operator=(PlayWorld const && other) = delete;

	uint32_t CreatePlayer(Position const & position, Velocity const & velocities);

	Position & Positions(uint32_t id);
	Velocity & Velocities(uint32_t id);

private:
	std::array<Position, settings::ENTITY_COUNT> positions_{};
	std::array<Velocity, settings::ENTITY_COUNT> velocities_{};
};

#endif /* PLAYWORLD_H_ */