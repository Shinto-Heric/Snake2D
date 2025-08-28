#include "SettingsPopup.h"
#include <iostream>

SettingsPopup::SettingsPopup()
    : PopupBase("Settings")
{
    // Example buttons
    Button musicBtn;
    musicBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    musicBtn.SetCellSize(32);
    musicBtn.SetText("Music", &m_assets.GetFont("button"), 24);
    musicBtn.SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    musicBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    musicBtn.SetGridPosition({ 5, 5 });
    musicBtn.SetCallback([]() { std::cout << "Music toggled!\n"; });

    Button soundBtn;
    soundBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    soundBtn.SetCellSize(32);
    soundBtn.SetText("Sound", &m_assets.GetFont("button"), 24);
    soundBtn.SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    soundBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    soundBtn.SetGridPosition({ 5, 7 });
    soundBtn.SetCallback([]() { std::cout << "Sound toggled!\n"; });

    Button instructionsBtn;
    instructionsBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    instructionsBtn.SetCellSize(32);
    instructionsBtn.SetText("Instructions", &m_assets.GetFont("button"), 24);
    instructionsBtn.SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    instructionsBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    instructionsBtn.SetGridPosition({ 5, 9 });
    instructionsBtn.SetCallback([]() { std::cout << "Instructions!\n"; });

    Button snakeColorBtn;
    snakeColorBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    snakeColorBtn.SetCellSize(32);
    snakeColorBtn.SetText("Snake Color", &m_assets.GetFont("button"), 24);
    snakeColorBtn.SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    snakeColorBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    snakeColorBtn.SetGridPosition({ 5, 11 });
    snakeColorBtn.SetCallback([]() { std::cout << "Change snake color!\n"; });

    m_buttons.push_back(musicBtn);
    m_buttons.push_back(soundBtn);
    m_buttons.push_back(instructionsBtn);
    m_buttons.push_back(snakeColorBtn);
}

void SettingsPopup::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons)
        btn.HandleInput(event, window);
}

void SettingsPopup::Update(sf::Time dt) {
    PopupBase::Update(dt);
    for (auto& btn : m_buttons)
        btn.Update(dt); // optional button animation
}

void SettingsPopup::Render(sf::RenderWindow& window) {
    PopupBase::Render(window);
    for (auto& btn : m_buttons)
        btn.Render(window);
}
