//Author: Michal Becmer - D00256088
#include "../../headers/core/input_manager.hpp"
#include <iostream>

namespace core {

    InputManager::InputManager() = default;

    void InputManager::Update() {
        keyboard_active_ = false;
        controller_active_ = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			keyboard_active_ = true;
        }

        if (sf::Joystick::isButtonPressed(0, 0)) {
            controller_active_ = true;
        }
    }

    bool InputManager::IsKeyboardActive() const {
        return keyboard_active_;
    }

    bool InputManager::IsControllerActive() const {
        return controller_active_;
    }

}