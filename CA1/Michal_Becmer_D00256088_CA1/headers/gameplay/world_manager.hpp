#pragma once
#include <memory>
#include <vector>
#include "../gameplay/entity.hpp"
#include "../gameplay/player.hpp"
#include "../gameplay/platform.hpp"
#include "../core/input_manager.hpp"
#include "../core/physics_engine.hpp"

namespace gameplay {
    class WorldManager {
    public:
        WorldManager(core::PhysicsEngine& physics_engine);

        gameplay::Player* SpawnPlayer(const core::PlayerInput& input, const sf::Vector2f& position, const sf::Color& color);
        gameplay::Platform* SpawnPlatform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

        void Update(float deltaTime, const core::InputManager& input_manager);
        void Render(sf::RenderWindow& window);

        const std::vector<std::unique_ptr<Entity>>& GetEntities() const { return entities_; }
        size_t GetPlayerCount() const;

    private:
        std::vector<std::unique_ptr<Entity>> entities_;
        core::PhysicsEngine& physics_engine_;
    };
}