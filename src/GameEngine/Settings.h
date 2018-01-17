#ifndef SETTINGS_H
#define SETTINGS_H

#include <bitset>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <unordered_map>

namespace ge {
	namespace Settings {
		static constexpr uint32_t EntitiesCount = 100;
		static constexpr uint32_t ComponentsCount = 100;
	};

	namespace Layer {
		static constexpr int32_t UI = 0;
		static constexpr int32_t Background = -1;
	}

	namespace Resources {
		enum Type {
			Texture,
			Font,
			Sound
		};
	}

	using Component = std::bitset<Settings::ComponentsCount>;
	using Entity = Component;
	using PrioritizedDrawable = std::pair<int32_t , std::shared_ptr<sf::Drawable>>;

	namespace Components {
		static constexpr Component None = 0;
	}
}

#endif /*SETTINGS_H*/