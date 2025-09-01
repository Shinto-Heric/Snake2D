#include "ExitPopup.h"
#include "ScreenManager.h"
#include "Game.h"
#include <iostream>

ExitPopup::ExitPopup()
    : PopupBase("Exit Game")
{
    // --- Quit Button (Red) ---
    auto quitBtn = std::make_unique<Button>();
    quitBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    quitBtn->SetCellSize(32);
    quitBtn->SetText("Quit", &m_assets.GetFont("button"), 24);
    quitBtn->SetBackgroundColors(sf::Color(200, 50, 50), sf::Color(255, 100, 100));
    quitBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    quitBtn->SetGridPosition({ 5, 10 });
    quitBtn->SetCallback([]() {
        if (auto game = ScreenManager::GetInstance().GetGame())
            game->CloseWindow();
        });

    // --- Cancel Button (Gray) ---
    auto cancelBtn = std::make_unique<Button>();
    cancelBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    cancelBtn->SetCellSize(32);
    cancelBtn->SetText("Cancel", &m_assets.GetFont("button"), 24);
    cancelBtn->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    cancelBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    cancelBtn->SetGridPosition({ 5, 12 });
    cancelBtn->SetCallback([this]() {
        this->ClosePopup();
        });

    // Optional: Back to Main Menu
    auto menuBtn = std::make_unique<Button>();
    menuBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    menuBtn->SetCellSize(32);
    menuBtn->SetText("Main Menu", &m_assets.GetFont("button"), 24);
    menuBtn->SetBackgroundColors(sf::Color(50, 50, 200), sf::Color(100, 100, 255));
    menuBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    menuBtn->SetGridPosition({ 5, 14 });
    menuBtn->SetCallback([]() {
        ScreenManager::GetInstance().SwitchToMainMenu();
        });

    m_buttons.push_back(std::move(quitBtn));
    m_buttons.push_back(std::move(cancelBtn));
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
