//Author: Michal Becmer - D00256088
#pragma once

#include <SFML/Window.hpp>
#include <vector>
#include <unordered_map>

namespace core {
	//Enum for different input types
	enum class InputDeviceType {
		Keyboard,
		Controller
	};

	//Structure to represent a players input mapping
	struct PlayerInput {
		InputDeviceType device_type;
		unsigned int device_id;
	};

	struct InputBinding {
		InputDeviceType device_type;
		unsigned int device_id;
		int key_or_button;
		int axis = -1;
		int axis_direction = 0;
	};

	struct ActionMapping {
		std::string action_name;
		std::vector<InputBinding> bindings;
	};

	class InputManager {
	public:
		InputManager();
		//InputManager(unsigned int player_count);

		void Update();

		bool IsKeyboardActive() const;
		bool IsControllerActive() const;

		//Future implementation for handling multiple players
		bool IsActionPressed(const std::string& action, InputDeviceType device_type, unsigned int device_id = 0) const;
		const std::vector<PlayerInput>& GetPlayerInputs() const;
		//float GetAxis(unsigned int player_index, unsigned int axis) const;
		//void SetPlayerInput(unsigned int player_index, const PlayerInput& input);
		//unsigned int GetPlayerCount() const;

	private:
		//Store per player input states (buttons, axes...)
		std::vector<std::unordered_map<std::string, bool>> action_states_;
		std::vector<std::vector<float>> axis_states_;

		std::vector<PlayerInput> player_inputs_;
		std::vector<ActionMapping> action_mappings_;

		bool keyboard_active_ = false;
		bool controller_active_ = false;
	};
}