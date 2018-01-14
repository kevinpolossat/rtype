#include "IntroWorld.h"

uint32_t IntroWorld::CreateButton(ge::Component const & component, Position const & position, Text const & text, Input const & input) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component;
	positions_[id] = position;
	texts_[id] = text;
	inputs_[id] = input;
	return id;
}

Position & IntroWorld:: Positions(uint32_t id) {
	return positions_[id];
}

Text & IntroWorld::Texts(uint32_t id) {
	return texts_[id];
}

Input & IntroWorld::Inputs(uint32_t id) {
	return inputs_[id];
}
