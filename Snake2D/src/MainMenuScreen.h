#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include "Game.h"
#include <vector>
#include <memory>
#include <iostream>

class MainMenuScreen : public BaseScreen {
private:
    Game* m_game;                   // Pointer to main game for switching screens
    ConfigManager& m_config;
    AssetManager& m_assets;
    std::vector<Button> m_buttons;
    sf::Text m_titleText;
    sf::Font* m_titleFont = nullptr;
public:
    MainMenuScreen(Game* game, ConfigManager& config, AssetManager& assets);
    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
