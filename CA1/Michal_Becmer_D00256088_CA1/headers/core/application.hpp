//Author: Michal Becmer - D00256088
#pragma once

#include <SFML/Graphics.hpp>
#include "input_manager.hpp"
#include "../gameplay/player.hpp"

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
		gameplay::Player player_;;
		void ProcessEvents();
		void Update();
		void Render();
	};
}