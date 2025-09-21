//Author: Michal Becmer - D00256088
#pragma once

#include <SFML/Graphics.hpp>

namespace states {
	//Abstract base class for different game states
	class GameState {
	public:
		virtual ~GameState() = default;

		virtual void HandleEvent(const sf::Event& event) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(sf::RenderWindow& window) = 0;
	};
}