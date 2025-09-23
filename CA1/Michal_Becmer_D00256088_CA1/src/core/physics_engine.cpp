#include "../../headers/core/physics_engine.hpp"

namespace core {
	void PhysicsEngine::Update(float deltaTime, std::vector<gameplay::Entity*>& entities) {
		for(auto* entity : entities) {
			if (entity -> IsDynamic()) {
				auto velocity = entity->GetVelocity();
				velocity += gravity_ * deltaTime;
				entity->SetVelocity(velocity);

				auto position = entity->GetPosition();
				position += velocity * deltaTime;
				entity->SetPosition(position);
			}
		}
	}

	void PhysicsEngine::SetGravity(const sf::Vector2f& gravity) {
		gravity_ = gravity;
	}
}