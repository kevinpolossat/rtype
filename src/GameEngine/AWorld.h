#ifndef AWORLD_H_
#define AWORLD_H_

#include <bitset>
#include <array>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Entity/Component.h"

namespace ge {
	class AWorld {
	public:
		AWorld() = default;
		AWorld(AWorld const &other) = delete;
		AWorld(AWorld &&other) = delete;
		virtual ~AWorld() = default;

		AWorld &operator=(AWorld const &other) = delete;
		AWorld &operator=(AWorld &&other) = delete;

		GameObject &Entities(uint32_t id);

	protected:
		std::vector<GameObject> entities_;
	};
}

#endif /* AWORLD_H_ */
