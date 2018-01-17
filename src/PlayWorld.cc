#include "PlayWorld.h"

void PlayWorld::CreatePlayer(Vector2D const & t_position, std::string t_textureName, Vector2D const & t_velocity)
{
	GameObject * g = new GameObject();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Sprite>(t_textureName, 1);
	g->AddComponent<Velocity>(t_velocity);
	this->players.push_back(g);
}
