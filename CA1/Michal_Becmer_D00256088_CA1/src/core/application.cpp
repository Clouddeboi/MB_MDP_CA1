//Author: Michal Becmer - D00256088
#include "../../headers/core/application.hpp"
#include "../../headers/core/input_manager.hpp"


namespace core {

    sf::Clock clock;

    Application::Application()
        : window_(sf::VideoMode({ 1280, 720 }), "SFML Game Engine"),
        input_manager_() {
    }

    Application::~Application() = default;

    void Application::Run() {
        float deltaTime = clock.restart().asSeconds();
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

            if (players_.size() < input_manager_.GetPlayerInputs().size()) {
                for (size_t i = players_.size(); i < input_manager_.GetPlayerInputs().size(); ++i) {
                    sf::Vector2f spawnPos = (i == 0) ? sf::Vector2f(400.f, 360.f) : sf::Vector2f(880.f, 360.f);
                    gameplay::Player player(input_manager_.GetPlayerInputs()[i]);
                    player.SetColor(i == 0 ? sf::Color::Blue : sf::Color::Red);
                    players_.push_back(player);
                }
            }

            for (auto& player : players_) {
                player.Update(deltaTime, input_manager_);
            }

            window_.clear();

            window_.draw(shape);
            window_.draw(shape2);

            for (auto& player : players_) {
                player.Render(window_);
            }

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