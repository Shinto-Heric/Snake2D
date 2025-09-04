#pragma once
#include <SFML/Graphics.hpp>

class BaseScreen {
public:
    virtual void HandleInput(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void Update(sf::Time dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~BaseScreen() = default;
};
