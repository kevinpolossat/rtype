#include "ResourcesManager.h"

sf::Texture & ResourcesManager::Texture(std::string const & name) {
	return textures_[name];
}

void ResourcesManager::LoadTextures(std::unordered_map<std::string, std::string> const & files) {
	for (auto & file : files) {
		LoadTexture(file.first, file.second);
	}
}

void ResourcesManager::LoadTexture(std::string const & name, std::string const & file) {
	sf::Texture texture;
	if (textures_.find(name) == textures_.end() && texture.loadFromFile(file)) {
		textures_.insert(std::pair<std::string, sf::Texture>(name, texture));
	}
}

sf::Font & ResourcesManager::Font(std::string const & name) {
	return fonts_[name];
}

void ResourcesManager::LoadFonts(std::unordered_map<std::string, std::string> const & files) {
	for (auto & file : files) {
		LoadFont(file.first, file.second);
	}
}

void ResourcesManager::LoadFont(std::string const & name, std::string const & file) {
	sf::Font font;
	if (fonts_.find(name) == fonts_.end() && font.loadFromFile(file)) {
		fonts_.insert(std::pair<std::string, sf::Font>(name, font));
	}
}
