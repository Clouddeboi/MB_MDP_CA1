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

		void SetVelocity(const sf::Vector2f& velocity) { velocity_ = velocity; }
		sf::Vector2f GetVelocity() const { return velocity_; }

		void SetDynamic(bool isDynamic) { is_dynamic_ = isDynamic; }
		bool IsDynamic() const { return is_dynamic_; }

		void SetMass(float mass) { mass_ = mass; }
		float GetMass() const { return mass_; }
		virtual sf::FloatRect GetBounds() const = 0;

		virtual void OnCollision(Entity& other, const sf::FloatRect& overlap) {}

		static bool CheckCollision(const Entity& a, const Entity& b) {
			const sf::FloatRect boundsA = a.GetBounds();
			const sf::FloatRect boundsB = b.GetBounds();
			//Manual AABB check
			return (boundsA.position.x < boundsB.position.x + boundsB.size.x) &&
				(boundsA.position.x + boundsA.size.x > boundsB.position.x) &&
				(boundsA.position.y < boundsB.position.y + boundsB.size.y) &&
				(boundsA.position.y + boundsA.size.y > boundsB.position.y);
		}

	protected:
		sf::Vector2f position_;
		sf::Vector2f velocity_{ 0.f, 0.f };
		bool is_dynamic_{ true };
		float mass_{ 1.0f };
	};
}