#include "Game.h"
#include "BaseScreen.h"
#include "MainMenuScreen.h"
#include <iostream>

Game::Game()
    : config(ConfigManager::GetInstance())
    , assets(AssetManager::GetInstance())
    , m_currentState(GameState::MainMenu)
{
    LoadConfig();
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), m_windowTitle);
    m_window.setFramerateLimit(60);

    InitGame();
}

Game::~Game() {
    // All dynamic memory for screens is handled by unique_ptr
}

void Game::LoadConfig() {
    m_windowWidth = config.GetWindowWidth();
    m_windowHeight = config.GetWindowHeight();
    m_windowTitle = config.GetWindowTitle();
}

void Game::InitGame() {
    // Load all assets first
    LoadAssets();

    // Start with Main Menu
    SwitchToScreen(std::make_unique<MainMenuScreen>(this, config, assets));

    std::cout << "Game initialized and MainMenuScreen loaded." << std::endl;
}
void Game::SetGameState(GameState currentState)
{
    m_currentState = currentState;
}

void Game::LoadAssets() {
    LoadTextures();
    LoadFonts();
}

void Game::LoadTextures() {
    std::vector<std::string> textureKeys = {
        "grass_grid", "snake_head", "snake_body",
        "food", "button_bg", "music_button", "effects_button"
    };

    for (auto& key : textureKeys)
        assets.LoadTexture(key, config.GetTexturePath(key));
}

void Game::LoadFonts() {
    std::vector<std::string> fontKeys = { "body", "button", "title" };
    for (auto& key : fontKeys)
        assets.LoadFont(key, config.GetFontPath(key));
}

void Game::Run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();

        HandleEvents();
        Update(dt);
        Render();
    }
}

void Game::HandleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (m_currentScreen)
            m_currentScreen->HandleInput(event, m_window);
    }
}

void Game::Update(sf::Time dt) {
    if (m_currentScreen)
        m_currentScreen->Update(dt);
}

void Game::Render() {
    m_window.clear(sf::Color::Black);

    if (m_currentScreen)
        m_currentScreen->Render(m_window);

    m_window.display();
}

void Game::SwitchToScreen(std::unique_ptr<BaseScreen> newScreen) {
    m_currentScreen = std::move(newScreen);
}
void Game::CloseWindow()
{

}