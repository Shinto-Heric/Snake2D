#include "MainMenuScreen.h"
#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "SettingsPopup.h"
#include "GameOverPopup.h"
MainMenuScreen::MainMenuScreen()
    : m_config(ConfigManager::GetInstance()), m_assets(AssetManager::GetInstance())
{
    // Title
    m_titleFont = &m_assets.GetFont("title");
    m_titleText.setFont(*m_titleFont);
    m_titleText.setString("Snake 2D");
    m_titleText.setCharacterSize(72);
    m_titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f);
    m_titleText.setPosition(static_cast<float>(m_config.GetWindowWidth()) / 2.f, 200.f);

    // Play button
    Button playBtn;
    playBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    playBtn.SetCellSize(32);
    playBtn.SetText(m_config.GetButtonText("main_menu", "start"), &m_assets.GetFont("button"), 30);
    playBtn.SetGridPosition({ 10, 12 });
    playBtn.SetBackgroundColors(sf::Color(50, 200, 50), sf::Color(100, 255, 100));
    playBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    playBtn.SetCallback([]() {
        ScreenManager::GetInstance().SetScreen(
            std::make_unique<GameplayScreen>()
        );
        });

    // Settings button
    Button settingsBtn;
    settingsBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    settingsBtn.SetCellSize(32);
    settingsBtn.SetText(m_config.GetButtonText("main_menu", "settings"), &m_assets.GetFont("button"), 30);
    settingsBtn.SetGridPosition({ 10, 14 });
    settingsBtn.SetBackgroundColors(sf::Color(50, 50, 200), sf::Color(100, 100, 255));
    settingsBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    settingsBtn.SetCallback([this]() { OpenSettingsPopup(); });

    // Exit button
    Button exitBtn;
    exitBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    exitBtn.SetCellSize(32);
    exitBtn.SetText(m_config.GetButtonText("main_menu", "exit"), &m_assets.GetFont("button"), 30);
    exitBtn.SetGridPosition({ 10, 16 });
    exitBtn.SetBackgroundColors(sf::Color(200, 50, 50), sf::Color(255, 100, 50));
    exitBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    exitBtn.SetCallback([]() { ScreenManager::GetInstance().ShowPopup(std::make_unique<GameOverPopup>(6,7)); });

    m_buttons.push_back(playBtn);
    m_buttons.push_back(settingsBtn);
    m_buttons.push_back(exitBtn);
}

void MainMenuScreen::OpenSettingsPopup() {
    ScreenManager::GetInstance().ShowPopup(std::make_unique<SettingsPopup>());
}

void MainMenuScreen::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons)
        btn.HandleInput(event, window);
}

void MainMenuScreen::Update(sf::Time dt) {
    m_titleTime += dt.asSeconds();
    float scale = 1.f + 0.05f * std::sin(m_titleTime * 2.f);
    m_titleText.setScale(scale, scale);
    sf::Uint8 colorValue = static_cast<sf::Uint8>(127 + 128 * std::sin(m_titleTime * 3.f));
    m_titleText.setFillColor(sf::Color(255, colorValue, 0));

    for (auto& btn : m_buttons)
        btn.Update(dt);
}

void MainMenuScreen::Render(sf::RenderWindow& window) {
    window.clear(sf::Color(30, 30, 60));
    window.draw(m_titleText);
    for (auto& btn : m_buttons)
        btn.Render(window);
}
