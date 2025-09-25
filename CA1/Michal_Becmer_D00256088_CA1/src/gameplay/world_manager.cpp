#include "../../headers/gameplay/world_manager.hpp"

namespace gameplay {

    WorldManager::WorldManager(core::PhysicsEngine& physics_engine)
        : physics_engine_(physics_engine) {
    }

    Player* WorldManager::SpawnPlayer(const core::PlayerInput& input, const sf::Vector2f& position, const sf::Color& color) {
        auto player = std::make_unique<Player>(input);
        player->SetPosition(position);
        player->SetColor(color);
        Player* ptr = player.get();
        entities_.push_back(std::move(player));
        return ptr;
    }

    Platform* WorldManager::SpawnPlatform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
        auto platform = std::make_unique<Platform>(position, size, color);
        Platform* ptr = platform.get();
        entities_.push_back(std::move(platform));
        return ptr;
    }

    void WorldManager::Update(float deltaTime, const core::InputManager& input_manager) {
        for (auto& entity : entities_) {
            entity->Update(deltaTime, input_manager);
        }

        std::vector<Entity*> dynamic_entities;
        for (auto& entity : entities_) {
            if (entity->IsDynamic()) {
                dynamic_entities.push_back(entity.get());
            }
        }
        physics_engine_.Update(deltaTime, dynamic_entities);

        HandleCollisions();
    }

    void WorldManager::Render(sf::RenderWindow& window) {
        for (auto& entity : entities_) {
            entity->Render(window);
        }
    }

    size_t WorldManager::GetPlayerCount() const {
        size_t count = 0;
        for (const auto& entity : entities_) {
            if (dynamic_cast<Player*>(entity.get())) {
                ++count;
            }
        }
        return count;
    }

	//We let each entity handle its own collision response
	//This just uses AABB to detect collisions and calculate overlap
    void WorldManager::HandleCollisions() {
        for (size_t i = 0; i < entities_.size(); ++i) {
            for (size_t j = i + 1; j < entities_.size(); ++j) {
                auto& a = *entities_[i];
                auto& b = *entities_[j];

                if (Entity::CheckCollision(a, b)) {
                    sf::FloatRect boundsA = a.GetBounds();
                    sf::FloatRect boundsB = b.GetBounds();

                    sf::Vector2f overlapPos(
                        std::max(boundsA.position.x, boundsB.position.x),
                        std::max(boundsA.position.y, boundsB.position.y)
                    );
                    sf::Vector2f overlapSize(
                        std::min(boundsA.position.x + boundsA.size.x, boundsB.position.x + boundsB.size.x) - overlapPos.x,
                        std::min(boundsA.position.y + boundsA.size.y, boundsB.position.y + boundsB.size.y) - overlapPos.y
                    );
                    sf::FloatRect overlap(overlapPos, overlapSize);

                    if (overlap.size.x > 0 && overlap.size.y > 0) {
                        a.OnCollision(b, overlap);
                        b.OnCollision(a, overlap);
                    }
                }
            }
        }
    }

}