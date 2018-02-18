#include "ResourcesManager.h"

void ge::ResourcesManager::SetVolume(uint32_t volume) {
	musics_->setVolume(volume);
}

sf::Texture & ge::ResourcesManager::Texture(std::string const & name) {
	return textures_[name];
}

sf::Font & ge::ResourcesManager::Font(std::string const & name) {
	return fonts_[name];
}

sf::SoundBuffer & ge::ResourcesManager::Sound(std::string const &name) {
	return sounds_[name];
}

void ge::ResourcesManager::LoadMusic(sf::Music & music) {
	musics_ = &music;
}
