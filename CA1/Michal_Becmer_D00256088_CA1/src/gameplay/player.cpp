#include "../../headers/gameplay/player.hpp"

namespace gameplay {
    Player::Player(const core::PlayerInput& input):
        assigned_input_(input), shape_(sf::Vector2f(50.0f, 50.0f)), color_(sf::Color::Green), speed_(0.75f), health_(100) {
        shape_.setFillColor(color_);
        shape_.setOrigin(sf::Vector2f(25.f, 25.f));
        position_ = sf::Vector2f(640.f, 360.f);
    }

    Player::~Player() = default;

    void Player::Update(float deltaTime, const core::InputManager& input_manager){
        sf::Vector2f velocity = GetVelocity();

        if (assigned_input_.device_type == core::InputDeviceType::Keyboard) {
            if (input_manager.IsActionPressed("Left", core::InputDeviceType::Keyboard)) {
                velocity.x -= speed_;
            }
            if (input_manager.IsActionPressed("Right", core::InputDeviceType::Keyboard)) {
                velocity.x += speed_;
            }
        }
        else if (assigned_input_.device_type == core::InputDeviceType::Controller) {
            if (input_manager.IsActionPressed("Left", core::InputDeviceType::Controller, assigned_input_.device_id)) {
                velocity.x -= speed_;
            }
            if (input_manager.IsActionPressed("Right", core::InputDeviceType::Controller, assigned_input_.device_id)) {
                velocity.x += speed_;
            }
        }

        SetVelocity(velocity);
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