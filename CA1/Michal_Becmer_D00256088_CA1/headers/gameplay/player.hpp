#pragma once

#include "entity.hpp"
#include "../core/input_manager.hpp"
#include <SFML/Graphics.hpp>

namespace gameplay {
	class Player : public Entity {
	public: 
		Player(const core::PlayerInput& input);
		~Player() override;

		void Update(float deltaTime, const core::InputManager& input_manager) override;
		void Render(sf::RenderWindow& window) override;

		void SetColor(const sf::Color& color);

	private:
		core::PlayerInput assigned_input_;
		sf::RectangleShape shape_;
		sf::Color color_;
		float speed_;
		int health_;
	};
}