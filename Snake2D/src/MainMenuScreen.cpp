#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(ConfigManager& config, AssetManager& assets)
    : m_config(config), m_assets(assets)
{
    // --- Screen background ---
    /*if (m_assets.HasTexture("main_menu_bg")) {
        m_bgTexture = &m_assets.GetTexture("main_menu_bg");
        m_bgSprite.setTexture(*m_bgTexture);
    }*/

    // --- Create Buttons ---
    Button playBtn, settingsBtn, exitBtn;

    // Play Button
    playBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    playBtn.SetCellSize(32);
    playBtn.SetText(m_config.GetButtonText("main_menu", "start"), &m_assets.GetFont("button"), 30);
    playBtn.SetGridPosition({ 10, 8 });
    //playBtn.SetColors(sf::Color::White, sf::Color::Yellow);
    playBtn.SetCallback([]() {
        std::cout << "Start Game pressed!" << std::endl;
        // Trigger game start
        });
    // Play button: green when idle, bright green on hover
    //playBtn.SetColors(sf::Color(50, 200, 50), sf::Color(100, 255, 100));

    
    

    // Settings Button
    settingsBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    settingsBtn.SetCellSize(32);
    settingsBtn.SetText(m_config.GetButtonText("main_menu", "settings"), &m_assets.GetFont("button"), 30);
    settingsBtn.SetGridPosition({ 10, 10 });
    settingsBtn.SetBackgroundColors(sf::Color::White, sf::Color::Yellow);
    settingsBtn.SetCallback([]() {
        std::cout << "Settings pressed!" << std::endl;
        // Open settings screen
        });
    // Settings button: blue idle, cyan hover
    settingsBtn.SetBackgroundColors(sf::Color(50, 50, 200), sf::Color(100, 100, 255));

    // Exit Button
    exitBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    exitBtn.SetCellSize(32);
    exitBtn.SetText(m_config.GetButtonText("main_menu", "exit"), &m_assets.GetFont("button"), 30);
    exitBtn.SetGridPosition({ 10, 12 });
    exitBtn.SetBackgroundColors(sf::Color::White, sf::Color::Yellow);
    exitBtn.SetCallback([]() {
        std::cout << "Exit pressed!" << std::endl;
        // Close the game
        });
    // Exit button: red idle, orange hover
    exitBtn.SetBackgroundColors(sf::Color(200, 50, 50), sf::Color(255, 100, 50));

    m_buttons.push_back(playBtn);
    m_buttons.push_back(settingsBtn);
    m_buttons.push_back(exitBtn);
}

void MainMenuScreen::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& btn : m_buttons) {
        btn.HandleInput(event, window);
    }
}

void MainMenuScreen::Update(sf::Time dt) {
    for (auto& btn : m_buttons)
        btn.Update(dt);
}

void MainMenuScreen::Render(sf::RenderWindow& window) {
    // Draw background
    if (m_bgTexture)
        window.draw(m_bgSprite);

    // Draw buttons
    for (auto& btn : m_buttons)
        btn.Render(window); // cell size for button placement
}
