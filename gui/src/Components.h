#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <bitset>
#include <SFML/Graphics.hpp>

using Bitset = std::bitset<6>;
using Entity = Bitset;

namespace component {
	// BASE
	Bitset const none = 0;
	Bitset const position = 1 << 0;
	Bitset const velocity = 1 << 1;
	Bitset const sprite = 1 << 2;
	Bitset const text = 1 << 3;
	Bitset const input = 1 << 4;
	Bitset const playerTag = 1 << 5;

	// COMPOSITION
	Bitset const button = position | text | input;
	Bitset const player = position | velocity | playerTag;
};

namespace settings {
	uint32_t const ENTITY_COUNT = 100;
};

struct Position {
	float x;
	float y;
};

struct Velocity {
	float x;
	float y;
};

struct Sprite {
	std::string textureName;
};

struct Text {
	std::string text;
	std::string fontName;
};

struct Input {
	int32_t id;
};

#endif /*COMPONENTS_H_*/