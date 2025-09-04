#include "ui/HUD.h"
#include <sstream>
#include "core/AssetManager.h"

HUD::HUD(sf::Font* font, const sf::Vector2f& scorePos, const sf::Vector2f& levelPos)
    : m_font(font), m_scorePosition(scorePos), m_levelPosition(levelPos)
{
    if (m_font) {
        m_scoreText.setFont(*m_font);
        m_scoreText.setCharacterSize(24);
        m_scoreText.setFillColor(m_textColor);
        m_scoreText.setPosition(m_scorePosition);
        m_scoreText.setString("Score: 0");

        m_levelText.setFont(*m_font);
        m_levelText.setCharacterSize(24);
        m_levelText.setFillColor(m_textColor);
        m_levelText.setPosition(m_levelPosition);
        m_levelText.setString("Level: 1");
    }
    m_heartTexture = &AssetManager::GetInstance().GetTexture("heart");
}

void HUD::SetScore(int score) {
    m_score = score;
    std::ostringstream ss;
    ss << "Score: " << m_score;
    m_scoreText.setString(ss.str());
}

void HUD::SetLevel(int level) {
    m_level = level;
    std::ostringstream ss;
    ss << "Level: " << m_level;
    m_levelText.setString(ss.str());
}

void HUD::SetLives(int lives) {
    m_lives = lives;
}

void HUD::Render(sf::RenderWindow& window) {
    window.draw(m_scoreText);
    window.draw(m_levelText);
    // Draw hearts for lives
    if (m_heartTexture) {
        for (int i = 0; i < m_lives; ++i) {
            sf::Sprite heartSprite;
            heartSprite.setTexture(*m_heartTexture);
            heartSprite.setPosition(startX + i * (m_heartTexture->getSize().x + spacing), startY);
            window.draw(heartSprite);
        }
    }
}
