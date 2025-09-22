//Author: Michal Becmer - D00256088
#include "../../headers/core/input_manager.hpp"
#include <iostream>

namespace core {

    InputManager::InputManager() = default;

    void InputManager::Update() {
        keyboard_active_ = false;
        controller_active_ = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (player_inputs_.size() < 2) {
				bool already_assigned = false;
                for (const auto& input : player_inputs_) {
                    if (input.device_type == InputDeviceType::Keyboard) {
                        already_assigned = true;
					}
                }
                if (!already_assigned) {
                    player_inputs_.push_back({ InputDeviceType::Keyboard, 0 });
                }
            }
        }

        unsigned int joystick_count = sf::Joystick::Count;
        for (unsigned int i = 0; i < joystick_count; ++i) {
            if (sf::Joystick::isConnected(i) && sf::Joystick::isButtonPressed(i, 0) || sf::Joystick::isButtonPressed(i, 1))  {
                if (player_inputs_.size() < 2) {
                    bool already_assigned = false;
                    for (const auto& input : player_inputs_) {
                        if (input.device_type == InputDeviceType::Controller && input.device_id == i)
                            already_assigned = true;
                    }
                    if (!already_assigned) {
                        player_inputs_.push_back({ InputDeviceType::Controller, i });
                    }
                }
            }
        }

        keyboard_active_ = false;
        controller_active_ = false;
        for (const auto& input : player_inputs_) {
            if (input.device_type == InputDeviceType::Keyboard) {
                keyboard_active_ = true;
            }
            if (input.device_type == InputDeviceType::Controller) {
                controller_active_ = true;
            }
        }
        
        //Debug - Show which device is assigned to which player
        for (size_t i = 0; i < player_inputs_.size(); ++i) {
            const auto& input = player_inputs_[i];
            std::cout << "Player " << (i + 1) << ": ";
            if (input.device_type == InputDeviceType::Keyboard) {
                std::cout << "Keyboard" << std::endl;
            }
            else if (input.device_type == InputDeviceType::Controller) {
                std::cout << "Controller " << input.device_id << std::endl;
            }
        }
    }

    bool InputManager::IsKeyboardActive() const {
        return keyboard_active_;
    }

    bool InputManager::IsControllerActive() const {
        return controller_active_;
    }

}