#include "popups/ExitPopup.h"
#include "core/ScreenManager.h"
#include "Game.h"
#include <iostream>
#include "screens/GameplayScreen.h"

ExitPopup::ExitPopup()
    : PopupBase("Exit Game")
{
    // --- Quit Button (Red) ---
    auto quitBtn = std::make_unique<Button>();
    quitBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    quitBtn->SetCellSize(32);
    quitBtn->SetText("YES", &m_assets.GetFont("button"), 24);
    quitBtn->SetBackgroundColors(sf::Color(200, 50, 50), sf::Color(255, 100, 100));
    quitBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    quitBtn->SetGridPosition({ 5, 11 });
    quitBtn->SetCallback([]() {
        if (auto game = ScreenManager::GetInstance().GetGame())
            game->CloseWindow();
        });

    // Optional: Back to Main Menu
    auto menuBtn = std::make_unique<Button>();
    menuBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    menuBtn->SetCellSize(32);
    menuBtn->SetText("NO", &m_assets.GetFont("button"), 24);
    menuBtn->SetBackgroundColors(sf::Color(50, 50, 200), sf::Color(100, 100, 255));
    menuBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    menuBtn->SetGridPosition({ 5, 13 });
    menuBtn->SetCallback([]() {
        ScreenManager::GetInstance().SetScreen(std::make_unique<GameplayScreen>());
        });

    m_buttons.push_back(std::move(quitBtn));
    m_buttons.push_back(std::move(menuBtn));
}

void ExitPopup::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons)
        btn->HandleInput(event, window);
}

void ExitPopup::Update(sf::Time dt) {
    PopupBase::Update(dt);
    for (auto& btn : m_buttons)
        btn->Update(dt);
}

void ExitPopup::Render(sf::RenderWindow& window) {
    PopupBase::Render(window);
    for (auto& btn : m_buttons)
        btn->Render(window);
}
