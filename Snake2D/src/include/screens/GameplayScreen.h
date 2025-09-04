#pragma once
#include "screens/BaseScreen.h"
#include "core/GameConfigManager.h"
#include "core/AssetManager.h"
#include "gameobjects/Snake.h"
#include "gameobjects/Grid.h"
#include "gameobjects/Food.h"
#include "ui/HUD.h"

static constexpr int POINTS_PER_LEVEL = 5;
static constexpr int POISON_FOOD_INTERVAL = 5;
static constexpr int SNAKE_SHRINK_SIZE = 3;

class GameplayScreen : public BaseScreen {
private:
    GameConfigManager& m_config;
    AssetManager& m_assets;

    Grid* m_grid = nullptr;
    Snake* m_snake = nullptr;
    Food* m_foodNormal = nullptr;
    Food* m_foodPoison = nullptr;
    HUD* m_hud = nullptr;

    int m_foodEatenCount = 0;
    int m_level = 1;
    
    int m_lives = 3;              // Initial lives
    

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
    GameplayScreen();
    ~GameplayScreen();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void TriggerGameOver();
    void Render(sf::RenderWindow& window) override;

    void HandleNormalFood();
    void HandleLevelUp();
    void HandlePoisonSpawn();
    void HandlePoisonFood();
    void HandleSelfCollision();
    bool IsGameOver() const { return m_gameOver; }
};