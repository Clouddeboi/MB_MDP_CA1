#pragma once

#include <vector>
#include "../gameplay/entity.hpp"

namespace core {
	class PhysicsEngine {
	public:
		void Update(float deltaTime, std::vector<gameplay::Entity*>& entities);
		void SetGravity(const sf::Vector2f& gravity);

	private:
		//9.81 is realistic gravity, however, for gameplay it has to be adjusted
		sf::Vector2f gravity_ = sf::Vector2f(0.f, 750.0f);
	};
}