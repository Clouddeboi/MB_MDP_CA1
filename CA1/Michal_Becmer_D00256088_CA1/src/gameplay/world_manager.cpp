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

    void WorldManager::HandleCollisions() {
        for (const auto& entityA : entities_) {
            Player* player = dynamic_cast<Player*>(entityA.get());
            if (!player) continue;

            sf::FloatRect playerBounds = player->GetBounds();

            for (const auto& entityB : entities_) {
                Platform* platform = dynamic_cast<Platform*>(entityB.get());
                if (!platform) continue;

                sf::FloatRect platformBounds = platform->GetBounds();

                auto overlap = playerBounds.findIntersection(platformBounds);

                if (overlap) {
                    sf::Vector2f playerPos = player->GetPosition();
                    playerPos.y = platformBounds.position.y - playerBounds.size.y / 2.f;
                    player->SetPosition(playerPos);

                    sf::Vector2f velocity = player->GetVelocity();
                    if (velocity.y > 0) velocity.y = 0;
                    player->SetVelocity(velocity);

                    playerBounds = player->GetBounds();
                }
            }
        }
    }

}