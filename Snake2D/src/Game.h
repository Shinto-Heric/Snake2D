#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "ConfigManager.h"
#include "AssetManager.h"

// Forward declaration
class BaseScreen;

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver
};

class Game {
private:
    // Window
    sf::RenderWindow m_window;
    int m_windowWidth;
    int m_windowHeight;
    std::string m_windowTitle;

    // Managers
    ConfigManager& config;
    AssetManager& assets;

    // Current active screen
    std::unique_ptr<BaseScreen> m_currentScreen;

    // Game state
    GameState m_currentState;

    // -------------------------
    // Initialization helpers
    // -------------------------
    void LoadConfig();
    void LoadAssets();
    void LoadTextures();
    void LoadFonts();

    void InitGame();
    // -------------------------
    // Game loop helpers
    // -------------------------
    void HandleEvents();
    void Update(sf::Time dt);
    void Render();

public:
    Game();
    ~Game();

    void Run();

    void SwitchToScreen(std::unique_ptr<BaseScreen> newScreen);
    void SetGameState(GameState currentState);
    void CloseWindow();

};
