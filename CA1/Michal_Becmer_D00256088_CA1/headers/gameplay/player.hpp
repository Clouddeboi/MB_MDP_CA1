#pragma once

#include "entity.hpp"
#include "../core/input_manager.hpp"
#include <SFML/Graphics.hpp>

namespace gameplay {
	class Player : public Entity {
	public: 
		Player();
		~Player() override;

		void Update(float deltaTime, const core::InputManager& input_manager) override;
		void Render(sf::RenderWindow& window) override;

		void SetColor(const sf::Color& color);

	private:
		sf::CircleShape shape_;
		sf::Color color_;
		float speed_;
		int health_;
	};
}