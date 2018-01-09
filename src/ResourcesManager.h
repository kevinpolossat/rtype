#ifndef RESOURCES_MANAGER_H_
#define RESSOURCES_MANAGER_H_

#include <unordered_map>
#include <SFML/Graphics.hpp>

class ResourcesManager {
public:
	ResourcesManager() = default;
	ResourcesManager(ResourcesManager const & other) = delete;
	ResourcesManager(ResourcesManager const && other) = delete;
	~ResourcesManager() = default;

	ResourcesManager & operator=(ResourcesManager const & other) = delete;
	ResourcesManager & operator=(ResourcesManager const && other) = delete;

	sf::Texture & Texture(std::string const & name);
	void LoadTextures(std::unordered_map<std::string, std::string> const & files);
	void LoadTexture(std::string const & name, std::string const & file);

	sf::Font & Font(std::string const & name);
	void LoadFonts(std::unordered_map<std::string, std::string> const & files);
	void LoadFont(std::string const & name, std::string const & file);

private:
	std::unordered_map<std::string, sf::Texture> textures_;
	std::unordered_map<std::string, sf::Font> fonts_;
};

#endif /*RESOURCES_MANAGER_H_*/