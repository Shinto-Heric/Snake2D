#include "popups/GameOverPopup.h"
#include "core/ScreenManager.h"
#include <iostream>
#include "core/SoundManager.h"
#include "screens/MainMenuScreen.h"
#include "screens/GameplayScreen.h"

GameOverPopup::GameOverPopup(int score, int level)
    : PopupBase("Game Over"), m_score(score), m_level(level)
{
    m_font = &m_assets.GetFont("body");

    // Score Text
    m_scoreText.setFont(*m_font);
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(35);
    m_scoreText.setFillColor(sf::Color::White);
    sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreBounds.width / 2.f, scoreBounds.height / 2.f);
    m_scoreText.setPosition(m_bgRect.getPosition().x, m_bgRect.getPosition().y - 125.f);

    // Level Text
    m_levelText.setFont(*m_font);
    m_levelText.setString("Level: " + std::to_string(m_level));
    m_levelText.setCharacterSize(35);
    m_levelText.setFillColor(sf::Color::White);
    sf::FloatRect levelBounds = m_levelText.getLocalBounds();
    m_levelText.setOrigin(levelBounds.width / 2.f, levelBounds.height / 2.f);
    m_levelText.setPosition(m_bgRect.getPosition().x, m_bgRect.getPosition().y - 90.f);

    // Retry Button
    Button retryBtn;
    retryBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    retryBtn.SetCellSize(32);
    retryBtn.SetText("Retry", &m_assets.GetFont("button"), 24);
    retryBtn.SetBackgroundColors(sf::Color(50, 200, 50), sf::Color(100, 255, 100));
    retryBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    retryBtn.SetGridPosition({ 10,13 });
    retryBtn.SetCallback([]() {
        ScreenManager::GetInstance().ClosePopup();
        ScreenManager::GetInstance().SetScreen(std::make_unique<GameplayScreen>());
        SoundManager::GetInstance().PlayMusic();
        });

    // Back to Main Menu Button
    Button backBtn;
    backBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    backBtn.SetCellSize(32);
    backBtn.SetText("Main Menu", &m_assets.GetFont("button"), 24);
    backBtn.SetBackgroundColors(sf::Color(100, 100, 200), sf::Color(150, 150, 255));
    backBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    backBtn.SetGridPosition({ 5,15 });
    backBtn.SetCallback([]() {
        ScreenManager::GetInstance().ClosePopup();
        ScreenManager::GetInstance().SetScreen(std::make_unique<MainMenuScreen>());
        SoundManager::GetInstance().PlayMusic();
        });

    m_buttons.push_back(retryBtn);
    m_buttons.push_back(backBtn);
}

void GameOverPopup::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons)
        btn.HandleInput(event, window);
}

void GameOverPopup::Update(sf::Time dt) {
    PopupBase::Update(dt);
    for (auto& btn : m_buttons)
        btn.Update(dt);
}

void GameOverPopup::Render(sf::RenderWindow& window) {
    PopupBase::Render(window);
    for (auto& btn : m_buttons)
        btn.Render(window);
    window.draw(m_scoreText);
    window.draw(m_levelText);
}
