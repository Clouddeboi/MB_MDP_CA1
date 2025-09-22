#include "../../headers/gameplay/player.hpp"

namespace gameplay {
    Player::Player(): 
        shape_(25.f),
        color_(sf::Color::Green),
        speed_(1.f),
        health_(100) {
        shape_.setFillColor(color_);
        shape_.setOrigin(sf::Vector2f(shape_.getRadius(), shape_.getRadius()));
        position_ = sf::Vector2f(640.f, 360.f);
    }

    Player::~Player() = default;

    void Player::Update(float deltaTime, const core::InputManager& input_manager){
        sf::Vector2f movement(0.f, 0.f);

        if (input_manager.IsActionPressed("Left", core::InputDeviceType::Keyboard)) {
            movement.x -= speed_ * deltaTime;
        }
        if (input_manager.IsActionPressed("Right", core::InputDeviceType::Keyboard)) {
            movement.x += speed_ * deltaTime;
        }
        if (input_manager.IsActionPressed("Left", core::InputDeviceType::Controller, 0)) {
            movement.x -= speed_ * deltaTime;
        }
        if (input_manager.IsActionPressed("Right", core::InputDeviceType::Controller, 0)) {
            movement.x += speed_ * deltaTime;
        }

        position_ += movement;
    }

    void Player::Render(sf::RenderWindow& window) {
        shape_.setPosition(position_);
        shape_.setFillColor(color_);
        window.draw(shape_);
    }

    void Player::SetColor(const sf::Color& color) {
        color_ = color;
    }
}