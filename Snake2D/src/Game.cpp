#include "Game.h"
#include "MainMenuScreen.h"
#include <iostream>
#include "SoundManager.h"

Game::Game()
    : config(ConfigManager::GetInstance())
    , assets(AssetManager::GetInstance())
    , m_currentState(GameState::MainMenu)
{
    LoadConfig();
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), m_windowTitle);
    m_window.setFramerateLimit(60);

    LoadAssets();
    LoadSounds();
    ScreenManager::GetInstance().Init(this);
    // Start with MainMenuScreen
    ScreenManager::GetInstance().SetScreen(
        std::make_unique<MainMenuScreen>()
    );
    SoundManager::GetInstance().LoadMusic(config.GetSoundPath("bgm"));
    SoundManager::GetInstance().PlayMusic();
}

Game::~Game() {}

void Game::LoadConfig() {
    m_windowWidth = config.GetWindowWidth();
    m_windowHeight = config.GetWindowHeight();
    m_windowTitle = config.GetWindowTitle();
}

void Game::LoadAssets() {
    LoadTextures();
    LoadFonts();
    LoadSounds();
}

void Game::LoadTextures() {
    std::vector<std::string> textureKeys = {
        "grass_grid", "snake_head", "snake_body", "heart", 
        "food", "button_bg", "music_on", "effects_on","music_off", "effects_off"
    };
    for (auto& key : textureKeys)
        assets.LoadTexture(key, config.GetTexturePath(key));
}

void Game::LoadFonts() {
    std::vector<std::string> fontKeys = { "body", "button", "title" };
    for (auto& key : fontKeys)
        assets.LoadFont(key, config.GetFontPath(key));
}

void Game::LoadSounds() {
    std::vector<std::string> effectsKeys = { "game_over" ,"eat", "poison_eat", "button_click", "button_toggle" };
    for (auto& key : effectsKeys)
        SoundManager::GetInstance().LoadEffect(key, config.GetSoundPath(key));
}

void Game::Run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            ScreenManager::GetInstance().HandleInput(event, m_window);
        }

        ScreenManager::GetInstance().Update(dt);

        m_window.clear(sf::Color::Black);
        ScreenManager::GetInstance().Render(m_window);
        m_window.display();
    }
}

void Game::SetGameState(GameState state) {
    m_currentState = state;
}

void Game::CloseWindow() {
    m_window.close();
}
