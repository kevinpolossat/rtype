#ifndef COMPONENTS_H_
#define COMPONENTS_H_

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
	int32_t priority;
};

struct Text {
	std::string text;
	std::string fontName;
};

struct Input {
	int32_t id;
};

#endif /*COMPONENTS_H_*/