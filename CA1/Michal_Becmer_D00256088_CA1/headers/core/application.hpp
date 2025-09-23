//Author: Michal Becmer - D00256088
#pragma once

#include <SFML/Graphics.hpp>
#include "input_manager.hpp"
#include "../gameplay/player.hpp"
#include "../core/physics_engine.hpp"

namespace core {
	class Application {

	public:
		//Constructor and Destructor
		Application();
		~Application();

		void Run();

	private:
		sf::RenderWindow window_;
		InputManager input_manager_;
		std::vector<gameplay::Player> players_;
		core::PhysicsEngine physics_engine_;
		void ProcessEvents();
		void Update();
		void Render();
	};
}