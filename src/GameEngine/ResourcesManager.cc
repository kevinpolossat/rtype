#include "ResourcesManager.h"

sf::Texture & ge::ResourcesManager::Texture(std::string const & name) {
	return textures_[name];
}

sf::Font & ge::ResourcesManager::Font(std::string const & name) {
	return fonts_[name];
}