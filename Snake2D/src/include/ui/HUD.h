#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD {
private:
    sf::Font* m_font;

    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Texture* m_heartTexture;

    int m_score = 0;
    int m_level = 1;
    int m_lives = 0;
    sf::Vector2f m_scorePosition;
    sf::Vector2f m_levelPosition;

    sf::Color m_textColor = sf::Color::White;

    float startX = 0.f;          // Starting X position for first heart
    float startY = 75;          // Y position for hearts
    float spacing = 10.f;         // Space between hearts

public:
    HUD(sf::Font* font, const sf::Vector2f& scorePos = { 10.f, 10.f }, const sf::Vector2f& levelPos = { 10.f, 40.f });

    void SetScore(int score);
    void SetLevel(int level);
    void SetLives(int lives);


    void Render(sf::RenderWindow& window);
};
