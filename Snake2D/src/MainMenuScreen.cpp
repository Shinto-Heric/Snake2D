#include "MainMenuScreen.h"
#include "GameplayScreen.h" // Make sure you have this screen implemented

MainMenuScreen::MainMenuScreen(Game* game, ConfigManager& config, AssetManager& assets)
    : m_game(game), m_config(config), m_assets(assets)
{
    // Title Text
    m_titleFont = &m_assets.GetFont("title"); // use a title font
    m_titleText.setFont(*m_titleFont);
    m_titleText.setString("Snake 2D");
    m_titleText.setCharacterSize(72);
    m_titleText.setFillColor(sf::Color::Yellow);

    // Center the title
    sf::FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f);
    m_titleText.setPosition(static_cast<float>(m_config.GetWindowWidth()) / 2.f, 200.f);
    // --- Play Button ---
    Button playBtn;
    playBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    playBtn.SetCellSize(32);
    playBtn.SetText(m_config.GetButtonText("main_menu", "start"), &m_assets.GetFont("button"), 30);
    playBtn.SetGridPosition({ 10, 12 });
    playBtn.SetBackgroundColors(sf::Color(50, 200, 50), sf::Color(100, 255, 100));
    playBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);

    playBtn.SetCallback([this]() {
        if (m_game) {
            // Switch to GameplayScreen
            m_game->SetGameState(GameState::Playing);
            m_game->SwitchToScreen(std::make_unique<GameplayScreen>(ConfigManager::GetInstance(), AssetManager::GetInstance()));
            std::cout << "GameplayScreen loaded!" << std::endl;
        }
        });

    // --- Settings Button ---
    Button settingsBtn;
    settingsBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    settingsBtn.SetCellSize(32);
    settingsBtn.SetText(m_config.GetButtonText("main_menu", "settings"), &m_assets.GetFont("button"), 30);
    settingsBtn.SetGridPosition({ 10, 14 });
    settingsBtn.SetBackgroundColors(sf::Color(50, 50, 200), sf::Color(100, 100, 255));
    settingsBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    settingsBtn.SetCallback([]() {
        std::cout << "Settings pressed!" << std::endl;
        });

    // --- Exit Button ---
    Button exitBtn;
    exitBtn.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    exitBtn.SetCellSize(32);
    exitBtn.SetText(m_config.GetButtonText("main_menu", "exit"), &m_assets.GetFont("button"), 30);
    exitBtn.SetGridPosition({ 10, 16 });
    exitBtn.SetBackgroundColors(sf::Color(200, 50, 50), sf::Color(255, 100, 50));
    exitBtn.SetTextColors(sf::Color::White, sf::Color::Yellow);
    exitBtn.SetCallback([this]() {
        if (m_game) {
            m_game->CloseWindow();  // Add a function in Game to close the window
        }
        });

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
        btn.Update(dt); // optional animation logic
}

void MainMenuScreen::Render(sf::RenderWindow& window) {
    window.clear(sf::Color(30, 30, 60));
    window.draw(m_titleText); // draw title

    for (auto& btn : m_buttons)
        btn.Render(window);
}
