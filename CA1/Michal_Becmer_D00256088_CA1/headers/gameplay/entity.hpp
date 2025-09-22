#pragma once
# include <SFML/Graphics.hpp>
#include "../core/input_manager.hpp"

namespace gameplay {
	class Entity {
	public:
		virtual ~Entity() = default;

		virtual void Update(float deltaTime, const core::InputManager& input_manager) = 0;
		virtual void Render(sf::RenderWindow& window) = 0;
		void SetPosition(const sf::Vector2f& position) { position_ = position; }
		sf::Vector2f GetPosition() const { return position_; }

	protected:
		sf::Vector2f position_;
	};
}