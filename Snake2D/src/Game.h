#pragma once
#include <SFML/Graphics.hpp>
#include "core/GameConfigManager.h"
#include "core/AssetManager.h"
#include "core/ScreenManager.h"

class Game {
private:
    sf::RenderWindow m_window;
    int m_windowWidth;
    int m_windowHeight;
    std::string m_windowTitle;

    GameConfigManager& config;
    AssetManager& assets;

    void LoadConfig();
    void LoadAssets();
    void LoadTextures();
    void LoadFonts();
    void LoadSounds();

public:
    Game();
    ~Game();

    void Run();
    void CloseWindow();
};
