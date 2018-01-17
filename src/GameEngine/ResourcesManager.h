#ifndef RESOURCES_MANAGER_H_
#define RESOURCES_MANAGER_H_

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Settings.h"

namespace ge {
	class ResourcesManager {
		template<class T>
		using Map = std::unordered_map<std::string, T>;

	public:
		ResourcesManager() = default;
		ResourcesManager(ResourcesManager const & other) = delete;
		ResourcesManager(ResourcesManager && other) = delete;
		~ResourcesManager() = default;

		ResourcesManager &operator=(ResourcesManager const & other) = delete;
		ResourcesManager &operator=(ResourcesManager && other) = delete;

		template<Resources::Type T>
		void Load(std::string const & name, std::string const & file) {
			switch (T) {
				case Resources::Texture:
					Load_<sf::Texture>(name, file, textures_, "texture");
					break;
				case Resources::Font:
					Load_<sf::Font>(name, file, fonts_, "font");
					break;
				case Resources::Sound:
					break;
				default:
					break;
			}
		}

		sf::Texture & Texture(std::string const & name);
		sf::Font & Font(std::string const & name);

	private:
		template<class T>
		void Load_(std::string const & name, std::string const & file, Map<T> & container, std::string const & type) {
			if (container.find(name) == container.end()) {
				T resource;
				if (resource.loadFromFile(file)) {
					container.insert(std::pair<std::string, T>(name, resource));
				} else {
					std::cerr << "ResourcesManager : Can't load " << file << std::endl;
				}
			} else {
				std::cerr << "ResourcesManager : " << type << " named " << name << " already exist" << std::endl;
			}
		}

		Map<sf::Texture> textures_;
		Map<sf::Font> fonts_;
	};
}

#endif /*RESOURCES_MANAGER_H_*/
