#include "ResourcesManager.h"

sf::Texture & ge::ResourcesManager::Texture(std::string const & name) {
	return textures_[name];
}

sf::Font & ge::ResourcesManager::Font(std::string const & name) {
	return fonts_[name];
}

sf::SoundBuffer & ge::ResourcesManager::Sound(std::string const &name) {
	return sounds_[name];
}

sf::Music & ge::ResourcesManager::Music(std::string const &name) {
	return *musics_[name];
}

void ge::ResourcesManager::LoadMusic_(std::string const & name, std::string const & file) {
	if (musics_.find(name) == musics_.end()) {
		std::unique_ptr<sf::Music> resource;
		if (resource->openFromFile(file)) {
			musics_.insert(std::pair<std::string, std::unique_ptr<sf::Music>>(name, std::move(resource)));
		} else {
			std::cerr << "ResourcesManager : Can't load " << file << std::endl;
		}
	} else {
		std::cerr << "ResourcesManager : music named " << name << " already exist" << std::endl;
	}
}
