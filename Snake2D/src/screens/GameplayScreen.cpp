#include "screens/GameplayScreen.h"
#include "core/ScreenManager.h"
#include "popups/GameOverPopup.h"
#include "core/SoundManager.h"

#include <iostream>

GameplayScreen::GameplayScreen()
    : m_config(GameConfigManager::GetInstance())
    , m_assets(AssetManager::GetInstance())
{

    // Init grid
    m_grid = new Grid(m_config.GetColumnSize(), m_config.GetRowSize(), m_config.GetCellSize(), &m_assets.GetTexture("grass_grid"));

    // Init HUD
    m_hud = new HUD(&m_assets.GetFont("body"));
    m_hud->SetLives(m_lives);
    // Init snake
    m_snake = new Snake(
        m_config.GetColumnSize(), m_config.GetRowSize(), m_config.GetCellSize(),
        &m_assets.GetTexture("snake_head"),
        &m_assets.GetTexture("snake_body")
    );

    // Init normal food
    m_foodNormal = new Food(m_config.GetGridWidth(), m_config.GetGridHeight(), &m_assets.GetTexture("food"));

    std::cout << "GameplayScreen initialized." << std::endl;
}

GameplayScreen::~GameplayScreen() {
    delete m_grid;
    delete m_snake;
    delete m_foodNormal;
    delete m_foodPoison;
    delete m_hud;
}

void GameplayScreen::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        Direction desiredDir = m_snake->GetDirection();

        switch (event.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W: desiredDir = Direction::Up; break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S: desiredDir = Direction::Down; break;
        case sf::Keyboard::Left:
        case sf::Keyboard::A: desiredDir = Direction::Left; break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D: desiredDir = Direction::Right; break;
        default: break;
        }

        m_snake->SetNextDirection(desiredDir);
    }
}

void GameplayScreen::Update(sf::Time dt) {
    if (m_gameOver) return;

    m_moveTimer += dt;
    if (m_moveTimer >= m_moveDelay) {
        m_moveTimer = sf::Time::Zero;
        m_snake->Move();

        HandleNormalFood();
        HandlePoisonFood();
        HandleSelfCollision();
    }
}

void GameplayScreen::HandleNormalFood() {
    if (m_snake->GetHeadPosition() != m_foodNormal->GetGridPosition())
        return;

    SoundManager::GetInstance().PlayEffect("eat");

    m_snake->Grow();
    m_foodEatenCount++;
    m_hud->SetScore(m_foodEatenCount);
    m_foodNormal->Respawn(m_snake->GetOccupiedPositions());

    HandleLevelUp();
    HandlePoisonSpawn();
}

void GameplayScreen::HandleLevelUp() {
    if (m_foodEatenCount % POINTS_PER_LEVEL != 0)
        return;

    m_level++;
    m_hud->SetLevel(m_level);

    m_moveDelay -= m_speedIncrement;
    m_defaultMoveDelay = m_moveDelay;
    if (m_moveDelay < m_minMoveDelay)
        m_moveDelay = m_minMoveDelay;
}

void GameplayScreen::HandlePoisonSpawn() {
    if (m_foodPoison) {
        delete m_foodPoison;
        m_foodPoison = nullptr;
    }

    if (m_foodEatenCount % POISON_FOOD_INTERVAL == 0 && !m_foodPoison) {
        m_foodPoison = new Food(m_config.GetGridWidth(), m_config.GetGridHeight(), &m_assets.GetTexture("food"), FoodType::Poison);
        m_foodPoison->Respawn(m_snake->GetOccupiedPositions());
    }
}

void GameplayScreen::HandlePoisonFood() {
    if (!m_foodPoison || m_snake->GetHeadPosition() != m_foodPoison->GetGridPosition())
        return;

    SoundManager::GetInstance().PlayEffect("poison_eat");
    m_snake->Shrink(SNAKE_SHRINK_SIZE);

    delete m_foodPoison;
    m_foodPoison = nullptr;

    m_hud->SetLives(--m_lives);

    if (m_lives <= 0) {
        TriggerGameOver();
    }
}

void GameplayScreen::HandleSelfCollision() {
    if (!m_snake->CheckSelfCollision()) return;

    TriggerGameOver();
    std::cout << "Game Over! Snake collided with itself." << std::endl;
}

void GameplayScreen::TriggerGameOver()
{
    m_gameOver = true;
    SoundManager::GetInstance().StopMusic();
    SoundManager::GetInstance().PlayEffect("game_over");
    ScreenManager::GetInstance().ShowPopup(
        std::make_unique<GameOverPopup>(m_foodEatenCount, m_level)
    );
}

void GameplayScreen::Render(sf::RenderWindow& window) {
    if (m_grid) m_grid->Render(window);
    if (m_foodNormal) m_foodNormal->Render(window);
    if (m_foodPoison) m_foodPoison->Render(window);
    if (m_snake) m_snake->Render(window);
    if (m_hud) m_hud->Render(window);
}
