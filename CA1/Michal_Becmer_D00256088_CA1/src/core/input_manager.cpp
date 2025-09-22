//Author: Michal Becmer - D00256088
//Reference: https://www.sfml-dev.org/tutorials/3.0/window/inputs/#joystick
#include "../../headers/core/input_manager.hpp"
#include <iostream>

namespace core {

    InputManager::InputManager() {
        action_mappings_.push_back({
            "Jump",
            {
				//Converts SFML key/button codes to our InputBinding structure(int)
                { InputDeviceType::Keyboard, 0, static_cast<int>(sf::Keyboard::Key::Space) },

                //Xbox and playstation controllers have different button mappings
                //For now we will just use the xbox controller mapping
                { InputDeviceType::Controller, 0, 0 },
            }
            });
    }

    void InputManager::Update() {
        if (IsActionPressed("Jump", InputDeviceType::Keyboard)) {
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
            if (sf::Joystick::isConnected(i)){
                if (IsActionPressed("Jump", InputDeviceType::Controller, i)) {
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

    bool InputManager::IsActionPressed(const std::string& action, InputDeviceType device_type, unsigned int device_id) const {
        for (const auto& mapping : action_mappings_) {
            if (mapping.action_name == action) {
                for (const auto& binding : mapping.bindings) {
                    if (binding.device_type == device_type) {
                        if (device_type == InputDeviceType::Keyboard) {
                            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(binding.key_or_button))) {
                                return true;
                            }
                        }
                        else if (device_type == InputDeviceType::Controller && binding.device_id == device_id) {
                            if (sf::Joystick::isConnected(device_id)) {
                                if (sf::Joystick::isButtonPressed(device_id, binding.key_or_button)) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
}