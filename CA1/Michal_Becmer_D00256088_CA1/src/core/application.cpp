//Author: Michal Becmer - D00256088
#include "../../headers/core/application.hpp"
#include "../../headers/core/input_manager.hpp"

namespace core {

    Application::Application()
        : window_(sf::VideoMode({ 1280, 720 }), "SFML Game Engine"),
        input_manager_() {
    }

    Application::~Application() = default;

    void Application::Run() {
		//Shapes used for debugging input detection
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        sf::CircleShape shape2(100.f);
		shape2.setFillColor(sf::Color::White);
		shape2.setPosition({1000, 0});

        while (window_.isOpen()) {
            while (const std::optional event = window_.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window_.close();
            }

            input_manager_.Update();

            if (input_manager_.IsKeyboardActive()) {
                shape.setFillColor(sf::Color::Red);
            }
            else if (input_manager_.IsControllerActive()) {
                shape2.setFillColor(sf::Color::Blue);
            }
            else {
                shape.setFillColor(sf::Color::Green);
                shape2.setFillColor(sf::Color::White);
            }

            window_.clear();

            window_.draw(shape);
            window_.draw(shape2);

            window_.display();
        }
    }

    void Application::ProcessEvents() {
        //TODO: event handling
    }

    void Application::Update() {
        //TODO: update game state
    }

    void Application::Render() {
        //TODO: rendering
    }

}