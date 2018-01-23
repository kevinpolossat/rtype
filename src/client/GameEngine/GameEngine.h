#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include <memory>
#include <stack>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <functional>
#include <queue>

#include "LoopTimer.h"
#include "Settings.h"
#include "AGameState.h"
#include "ResourcesManager.h"
#include "StatesManager.h"
#include "Component.h"
#include "Vector2D.h"
#include "NetworkManager.h"

namespace ge {
	// Forward declaration of StatesManager
	class StatesManager;

	class GameEngine {
	public:
		GameEngine();
		GameEngine(GameEngine const & other) = delete;
		GameEngine(GameEngine && other) = delete;
		~GameEngine() = default;

		GameEngine & operator=(GameEngine const & other) = delete;
		GameEngine & operator=(GameEngine && other) = delete;

		// CORE
		bool Init(std::string const & title, uint32_t width, uint32_t height, bool fullscreen);
		bool Init(std::string const & title, Vector2u const & size, bool fullscreen);
		void Run(std::string const & initState);
		void Draw(std::shared_ptr<sf::Drawable> const & drawable, int32_t display_level);
		Vector2u GetSize() const;
		void SetSize(uint32_t width, uint32_t height);
		void SetSize(Vector2u const & size);
		void SetFullscreen(bool fullscreen);
		std::vector<Vector2u> GetResolutionsModes() const;
		void Quit();

		// NETWORK
		void AddCommunication(std::shared_ptr<ge::network::NetworkCommunication> const & c);
		void RemoveCommunication(std::shared_ptr<ge::network::NetworkCommunication> const & c);

		// COMPONENTS
		/*
		bool AddComponent(std::string const & name);
		bool AddComponents(std::vector<std::string> const & names);
		bool AddComposedComponents(std::string const & name, std::vector<std::string> const & composition);
		bool Match(Entity const & entity, Component const & component) const;
		bool Match(Entity const & entity, std::string const & name) const;
		bool Match(std::string const & name1, std::string const & name2) const;
		Component const & operator[](std::string const & name) const;
		*/

		// STATES
		void AddState(std::string const & name, std::shared_ptr<AGameState> const & state);
		void ChangeState(std::string const & stateName);
		void PushState(std::string const & stateName);
		void PopState();

		// RESOURCES
		template<Resources::Type T>
		void Load(std::unordered_map<std::string, std::string> const & files) {
			for (auto & file : files) {
				Load<T>(file.first, file.second);
			}
		}

		template<Resources::Type T>
		void Load(std::string const & name, std::string const & file) {
			rm_->Load<T>(name, file);
		}

		void Load(Animator const & animator);

		sf::Texture & Texture(std::string const & name);
		sf::Font & Font(std::string const & name);

	private:
		// CORE
		void HandleEvents_();
		void Display_(float interpolation);

		sf::RenderWindow window_;
		std::string windowTitle_;

		// Using ptr here to avoid circular dependency
		std::unique_ptr<network::NetworkManager> nm_;
		std::unique_ptr<ResourcesManager> rm_;
		std::unique_ptr<StatesManager> st_;

		std::priority_queue<PrioritizedDrawable,
				std::vector<PrioritizedDrawable>,
				std::function<bool(PrioritizedDrawable, PrioritizedDrawable)>> toDraw_;
	};
}

#endif /*GAMEENGINE_H_*/
