#pragma once
#include "BaseScreen.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include "Snake.h"
#include "Grid.h"
#include "Food.h"
#include "HUD.h"

class GameplayScreen : public BaseScreen {
private:
    ConfigManager& m_config;
    AssetManager& m_assets;

    Grid* m_grid = nullptr;
    Snake* m_snake = nullptr;
    Food* m_foodNormal = nullptr;
    Food* m_foodPoison = nullptr;
    HUD* m_hud = nullptr;

    int m_foodEatenCount = 0;
    int m_level = 1;
    const int m_pointsPerLevel = 5;

    // Snake timing
    sf::Time m_moveTimer = sf::Time::Zero;
    sf::Time m_defaultMoveDelay = sf::seconds(0.2f);
    sf::Time m_moveDelay = m_defaultMoveDelay;
    sf::Time m_slowTimer = sf::Time::Zero;
    sf::Time m_slowDuration = sf::seconds(3.f);
    const sf::Time m_speedIncrement = sf::milliseconds(50);
    const sf::Time m_minMoveDelay = sf::milliseconds(50);

    bool m_gameOver = false;

public:
    GameplayScreen(ConfigManager& config, AssetManager& assets);
    ~GameplayScreen();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;

    bool IsGameOver() const { return m_gameOver; }
};
#pragma once
