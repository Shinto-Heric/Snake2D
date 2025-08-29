#pragma once
#include <SFML/Graphics.hpp>
#include "ConfigManager.h"
#include "AssetManager.h"
#include "ScreenManager.h"

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver
};

class Game {
private:
    sf::RenderWindow m_window;
    int m_windowWidth;
    int m_windowHeight;
    std::string m_windowTitle;

    ConfigManager& config;
    AssetManager& assets;
    GameState m_currentState;

    void LoadConfig();
    void LoadAssets();
    void LoadTextures();
    void LoadFonts();

public:
    Game();
    ~Game();

    void Run();
    void SetGameState(GameState state);
    void CloseWindow();
};
