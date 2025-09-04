#pragma once
#include "popups/PopupBase.h"
#include "ui/Button.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameOverPopup : public PopupBase {
private:
    std::vector<Button> m_buttons;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Font* m_font = nullptr;
    int m_score = 0;
    int m_level = 0;

public:
    GameOverPopup(int score, int level);

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};