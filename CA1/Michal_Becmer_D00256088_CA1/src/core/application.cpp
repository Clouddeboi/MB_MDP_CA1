//Author: Michal Becmer - D00256088
#include "../../headers/core/application.hpp"
#include "../../headers/core/input_manager.hpp"
#include "../../headers/core/physics_engine.hpp"

namespace core {

    sf::Clock clock;

    Application::Application()
        : window_(sf::VideoMode({ 1280, 720 }), "SFML Game Engine"),
        input_manager_(), physics_engine_(), world_manager_(physics_engine_) {
        world_manager_.SpawnPlatform(sf::Vector2f(0, 500), sf::Vector2f(800, 40), sf::Color::Green);
    }

    Application::~Application() = default;

    void Application::Run() {
        while (window_.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            while (const std::optional event = window_.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window_.close();
            }

            Update(deltaTime);
            Render();
        }
    }

    void Application::ProcessEvents() {
        //TODO: event handling
    }

    void Application::Update(float deltaTime) {
        input_manager_.Update();

        for (size_t i = world_manager_.GetPlayerCount(); i < input_manager_.GetPlayerInputs().size(); ++i) {
            sf::Vector2f spawnPos = (i == 0) ? sf::Vector2f(400.f, 360.f) : sf::Vector2f(880.f, 360.f);
            world_manager_.SpawnPlayer(
                input_manager_.GetPlayerInputs()[i],
                spawnPos,
                i == 0 ? sf::Color::Blue : sf::Color::Red
            );
        }

        world_manager_.Update(deltaTime, input_manager_);
    }

    void Application::Render() {
        window_.clear();
        //Shapes used for debugging input detection
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        sf::CircleShape shape2(100.f);
        shape2.setFillColor(sf::Color::White);
        shape2.setPosition({ 1000, 0 });

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

        window_.draw(shape);
        window_.draw(shape2);

        world_manager_.Render(window_);

        window_.display();
    }

}