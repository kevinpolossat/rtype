#ifndef SETTINGS_H
#define SETTINGS_H

#include <bitset>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <unordered_map>

#include "Vector2D.h"

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

	using PrioritizedDrawable = std::pair<int32_t , std::shared_ptr<sf::Drawable>>;

	using Vector2f = Vector2D<float>;
	using Vector2u = Vector2D<uint32_t>;
}

#endif /*SETTINGS_H*/