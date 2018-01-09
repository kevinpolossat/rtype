#ifndef WORLD_H_
#define WORLD_H_

#include "AWorld.h"

class IntroWorld : public AWorld {
public:
	IntroWorld() = default;
	IntroWorld(IntroWorld const & other) = delete;
	IntroWorld(IntroWorld const && other) = delete;
	~IntroWorld() override = default;

	IntroWorld & operator=(IntroWorld const & other) = delete;
	IntroWorld & operator=(IntroWorld const && other) = delete;

	uint32_t CreateButton(Position const & position, Text const & text, Input const & input);

	Position & Positions(uint32_t id);
	Text & Texts(uint32_t id);
	Input & Inputs(uint32_t id);

private:
	std::array<Position, settings::ENTITY_COUNT> positions_;
	std::array<Text, settings::ENTITY_COUNT> texts_;
	std::array<Input, settings::ENTITY_COUNT> inputs_;
};

#endif /* WORLD_H_ */