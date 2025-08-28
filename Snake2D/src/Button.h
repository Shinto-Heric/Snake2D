#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button : public Entity {
private:
    sf::Text m_text;
    sf::Font* m_font = nullptr;

    sf::Color m_idleColor = sf::Color::White;
    sf::Color m_hoverColor = sf::Color::Yellow;

    sf::Color m_bgIdleColor = sf::Color(100, 100, 100);
    sf::Color m_bgHoverColor = sf::Color(150, 150, 150);

    std::function<void()> m_callback;

    sf::Texture* m_bgTexture = nullptr;

    // --- Animation ---
    float m_targetScale = 1.f;
    float m_currentScale = 1.f;
    float m_scaleSpeed = 10.f;

public:
    Button() = default;

    void SetText(const std::string& text, sf::Font* font, unsigned int size = 24);
    void SetTextColors(sf::Color idle, sf::Color hover);
    void SetBackgroundColors(sf::Color idle, sf::Color hover);
    void SetCallback(std::function<void()> callback);
    void SetBackgroundTexture(sf::Texture* texture);

    void HandleInput(sf::Event& event, const sf::RenderWindow& window);
    void Update(sf::Time dt);
    void Render(sf::RenderWindow& window);
};
