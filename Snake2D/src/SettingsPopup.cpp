#include "SettingsPopup.h"
#include "AssetManager.h"
#include <iostream>
#include "ScreenManager.h"
#include "InstructionPopup.h"
#include "ToggleButton.h"
SettingsPopup::SettingsPopup()
    : PopupBase("Settings")
{
    // Music Button
    auto musicBtn = std::make_unique<ToggleButton>();
    musicBtn->SetTextures(
        &m_assets.GetTexture("music_on"),
        &m_assets.GetTexture("music_off")
    );
    musicBtn->SetCellSize(32);
    musicBtn->SetGridPosition({ 5, 9 });
    musicBtn->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    musicBtn->SetToggleCallback([](bool enabled) {
        std::cout << "Music: " << (enabled ? "ON" : "OFF") << std::endl;
        });
    // Sound Button
    auto soundBtn = std::make_unique<ToggleButton>();
    soundBtn->SetTextures(
        &m_assets.GetTexture("effects_on"),
        &m_assets.GetTexture("effects_off")
    );
    soundBtn->SetCellSize(32);
    soundBtn->SetGridPosition({ 5, 11 });
    soundBtn->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    soundBtn->SetToggleCallback([](bool enabled) {
        std::cout << "Effects: " << (enabled ? "ON" : "OFF") << std::endl;
        });
    // Instructions Button
    auto instructionsBtn = std::make_unique<Button>();
    instructionsBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    instructionsBtn->SetCellSize(32);
    instructionsBtn->SetText("Instructions", &m_assets.GetFont("button"), 24);
    instructionsBtn->SetGridPosition({ 5, 13 });
    instructionsBtn->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    instructionsBtn->SetTextColors(sf::Color::White, sf::Color::Yellow); 
    instructionsBtn->SetCallback([]() {
        ScreenManager::GetInstance().ShowPopup(
            std::make_unique<InstructionPopup>());
        });


    // Snake Color Button
    auto snakeColorBtn = std::make_unique<Button>();
    snakeColorBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    snakeColorBtn->SetCellSize(32);
    snakeColorBtn->SetText("Snake Color", &m_assets.GetFont("button"), 24);
    snakeColorBtn->SetGridPosition({ 5, 15 });
    snakeColorBtn->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    snakeColorBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    snakeColorBtn->SetCallback([]() { std::cout << "Change snake color\n"; });

    // Snake Color Button
    auto closeButton = std::make_unique<Button>();
    closeButton->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    closeButton->SetCellSize(32);
    closeButton->SetText("Back", &m_assets.GetFont("button"), 24);
    closeButton->SetGridPosition({ 5, 17 });
    closeButton->SetBackgroundColors(sf::Color(100, 100, 100), sf::Color(150, 150, 150));
    closeButton->SetTextColors(sf::Color::White, sf::Color::Yellow);
    closeButton->SetCallback([this]() { ClosePopup(); });

    m_buttons.push_back(std::move(musicBtn));
    m_buttons.push_back(std::move(soundBtn));
    m_buttons.push_back(std::move(instructionsBtn));
    m_buttons.push_back(std::move(snakeColorBtn));
    m_buttons.push_back(std::move(closeButton));
}

SettingsPopup::~SettingsPopup()
{
    m_buttons.clear();
}

void SettingsPopup::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons)
        btn->HandleInput(event, window);
}

void SettingsPopup::Update(sf::Time dt) {
    PopupBase::Update(dt);
    for (auto& btn : m_buttons)
        btn->Update(dt);
}

void SettingsPopup::Render(sf::RenderWindow& window) {
    PopupBase::Render(window);
    for (auto& btn : m_buttons)
        btn->Render(window);
}

void SettingsPopup::ClosePopup() {
    PopupBase::ClosePopup();
}

void SettingsPopup::OpenInstructionPopup()
{
}
