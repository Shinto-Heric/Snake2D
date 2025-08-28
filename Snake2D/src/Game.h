#pragma once
#include <SFML/Graphics.hpp>
#include "ConfigManager.h"
#include "AssetManager.h"

// Forward declarations for future classes
class BaseScreen;
class Grid;
class Snake;
class Food;
class HUD;

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
    // Game objects
    Grid* m_grid = nullptr;
    Snake* m_snake = nullptr;
    Food* m_foodNormal = nullptr;
    Food* m_foodPoison = nullptr;
    HUD* m_hud = nullptr;
    int m_foodEatenCount = 0;
    int m_level = 1;
    const int m_pointsPerLevel = 5;
    const sf::Time m_speedIncrement = sf::milliseconds(50);
    const sf::Time m_minMoveDelay = sf::milliseconds(50); // cap speed
    // Game state
    GameState m_currentState;
    std::unique_ptr<BaseScreen> m_currentScreen;

    sf::Time m_moveTimer = sf::Time::Zero;   // Timer for snake movement
    sf::Time m_defaultMoveDelay = sf::seconds(0.2f); // default snake speed
    sf::Time m_moveDelay = m_defaultMoveDelay;
    sf::Time m_slowTimer = sf::Time::Zero;
    sf::Time m_slowDuration = sf::seconds(3.f);     // slow effect lasts 3 seconds
    // -------------------------
    // Initialization helpers
    // -------------------------
    void LoadConfig();
    void InitGame();
    void LoadAssets();

    void LoadTextures();
    void LoadFonts();

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
};
