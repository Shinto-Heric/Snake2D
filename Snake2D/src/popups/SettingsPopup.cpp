#include <iostream>

#include "core/AssetManager.h"
#include "core/ScreenManager.h"
#include "core/SoundManager.h"
#include "popups/InstructionPopup.h"
#include "popups/SettingsPopup.h"
#include "ui/ToggleButton.h"

SettingsPopup::SettingsPopup()
    : PopupBase("Settings")
{
    // Music Button
    auto musicBtn = std::make_unique<ToggleButton>();
    musicBtn->SetTextures(
        &m_assets.GetTexture("music_on"),
        &m_assets.GetTexture("music_off")
    );
    musicBtn->SetGridPosition({ 5, 10 });
    musicBtn->SetBackgroundColors(sf::Color(70, 130, 180), sf::Color(100, 149, 237));
    musicBtn->SetToggleCallback([](bool enabled) {
        SoundManager::GetInstance().SetMusicEnabled(enabled);
        std::cout << "Music: " << (enabled ? "ON" : "OFF") << std::endl;
        });
    musicBtn->SetEnabled(SoundManager::GetInstance().IsMusicEnabled());
    // Sound Button
    auto soundBtn = std::make_unique<ToggleButton>();
    soundBtn->SetTextures(
        &m_assets.GetTexture("effects_on"),
        &m_assets.GetTexture("effects_off")
    );
    soundBtn->SetGridPosition({ 5, 12 });
    soundBtn->SetBackgroundColors(sf::Color(34, 139, 34), sf::Color(50, 205, 50));
    soundBtn->SetToggleCallback([](bool enabled) {
        SoundManager::GetInstance().SetEffectsEnabled(enabled);
        std::cout << "Effects: " << (enabled ? "ON" : "OFF") << std::endl;
        });
    soundBtn->SetEnabled(SoundManager::GetInstance().AreEffectsEnabled());


    // Instructions Button
    auto instructionsBtn = std::make_unique<Button>();
    instructionsBtn->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    instructionsBtn->SetText("Instructions", &m_assets.GetFont("button"), 24);
    instructionsBtn->SetGridPosition({ 5, 14 });
    instructionsBtn->SetBackgroundColors(sf::Color(255, 165, 0), sf::Color(255, 200, 0));
    instructionsBtn->SetTextColors(sf::Color::White, sf::Color::Yellow);
    instructionsBtn->SetCallback([]() {
        ScreenManager::GetInstance().ShowPopup(
            std::make_unique<InstructionPopup>());
        });


    auto closeButton = std::make_unique<Button>();
    closeButton->SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    closeButton->SetCellSize(32);
    closeButton->SetText("Back", &m_assets.GetFont("button"), 24);
    closeButton->SetGridPosition({ 5, 16 });
    closeButton->SetBackgroundColors(sf::Color(178, 34, 34), sf::Color(220, 20, 60));
    closeButton->SetTextColors(sf::Color::White, sf::Color::Yellow);
    closeButton->SetCallback([this]() { ClosePopup(); });

    m_buttons.push_back(std::move(musicBtn));
    m_buttons.push_back(std::move(soundBtn));
    m_buttons.push_back(std::move(instructionsBtn));
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
