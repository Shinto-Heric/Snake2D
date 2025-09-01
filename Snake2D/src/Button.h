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

    

protected:
    bool m_useAbsolutePosition = false;
    sf::Vector2f m_absolutePosition;
    // --- Animation ---
    float m_targetScale = 1.f;
    float m_currentScale = 1.f;
    float m_scaleSpeed = 10.f;
    std::string m_clickSound = "button_click";

public:
    Button() = default;

    void SetText(const std::string& text, sf::Font* font, unsigned int size = 24);
    void SetClickSound(const std::string& sound);
    void SetTextColors(sf::Color idle, sf::Color hover);
    void SetBackgroundColors(sf::Color idle, sf::Color hover);
    void SetCallback(std::function<void()> callback);
    void SetBackgroundTexture(sf::Texture* texture);
    void SetPosition(const sf::Vector2f& pos);

    void HandleInput(sf::Event& event, const sf::RenderWindow& window);
    void Update(sf::Time dt);
    void Render(sf::RenderWindow& window);
};
