//Author: Michal Becmer - D00256088
#include "../../headers/core/application.hpp"

namespace core {

    Application::Application()
        : window_(sf::VideoMode({ 1280, 720 }), "SFML Game Engine") {
    }

    Application::~Application() = default;

    void Application::Run() {
		//Draw a green circle for testing
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window_.isOpen()) {
            while (const std::optional event = window_.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window_.close();
            }

            window_.clear();
            window_.draw(shape);
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