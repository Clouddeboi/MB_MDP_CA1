#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>

namespace gameplay {
    class Platform : public Entity {
    public:
        Platform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White)
            : shape_(size) {
            SetPosition(position);
            shape_.setPosition(position);
            shape_.setFillColor(color);
            is_dynamic_ = false;
        }

        void Update(float deltaTime, const core::InputManager&) override {};

        void Render(sf::RenderWindow& window) override {
            shape_.setPosition(position_);
            window.draw(shape_);
        } 

        sf::FloatRect GetBounds() const override {
            return shape_.getGlobalBounds();
        }

    private:
        sf::RectangleShape shape_;
    };
}