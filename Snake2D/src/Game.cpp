#include "Game.h"
#include "Snake.h"
#include "HUD.h"
#include "Grid.h"
#include "Food.h"
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
    delete m_grid;
    delete m_snake;
    delete m_foodNormal;
    delete m_foodPoison;
    delete m_hud;
}

void Game::LoadConfig() {
    m_windowWidth = config.GetWindowWidth();
    m_windowHeight = config.GetWindowHeight();
    m_windowTitle = config.GetWindowTitle();
}

void Game::InitGame() {
    LoadAssets();

    // Initialize Grid
    m_grid = new Grid(32, 24, 32, &assets.GetTexture("grass_grid"));

    // Initialize HUD
    m_hud = new HUD(&assets.GetFont("body"));

    // Initialize Snake
    m_snake = new Snake(
        32, 24, 32,
        &assets.GetTexture("snake_head"),
        &assets.GetTexture("snake_body")
    );

    // Initialize Normal Food
    m_foodNormal = new Food(32, 24, &assets.GetTexture("food"));

    // Initialize Main Menu Screen
    SwitchToScreen(std::make_unique<MainMenuScreen>(config, assets));

    std::cout << "Game initialized with Grid, Snake, Food, HUD, and Main Menu." << std::endl;
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

        if (event.type == sf::Event::KeyPressed && m_currentState == GameState::Playing) {
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
}

void Game::Update(sf::Time dt) {
    if (m_currentState != GameState::Playing)
    {
        if (m_currentState == GameState::MainMenu)
            m_currentScreen->Update(dt);
        return;
    }

    // Slow effect timer
    if (m_slowTimer > sf::Time::Zero) {
        m_slowTimer -= dt;
        if (m_slowTimer <= sf::Time::Zero)
            m_moveDelay = m_defaultMoveDelay;
    }

    // Move snake based on move delay
    m_moveTimer += dt;
    if (m_moveTimer >= m_moveDelay) {
        m_moveTimer = sf::Time::Zero;
        m_snake->Move();

        // Check Normal Food
        if (m_snake->GetHeadPosition() == m_foodNormal->GetGridPosition()) {
            m_snake->Grow();
            m_foodEatenCount++;
            m_hud->SetScore(m_foodEatenCount);
            m_foodNormal->Respawn(m_snake->GetOccupiedPositions());

            // Level up
            if (m_foodEatenCount % m_pointsPerLevel == 0) {
                m_level++;
                m_hud->SetLevel(m_level);
                m_moveDelay -= m_speedIncrement;
                m_defaultMoveDelay = m_moveDelay;
                if (m_moveDelay < m_minMoveDelay)
                    m_moveDelay = m_minMoveDelay;
            }

            // Remove poison food if it exists
            if (m_foodPoison) {
                delete m_foodPoison;
                m_foodPoison = nullptr;
            }

            // Spawn poison food every 5 normal foods
            if (m_foodEatenCount % 5 == 0 && !m_foodPoison) {
                m_foodPoison = new Food(32, 24, &assets.GetTexture("food"), FoodType::Poison);
                m_foodPoison->Respawn(m_snake->GetOccupiedPositions());
            }
        }

        // Check Poison Food
        if (m_foodPoison && m_snake->GetHeadPosition() == m_foodPoison->GetGridPosition()) {
            m_snake->Shrink(3);
            m_foodEatenCount -= 3;
            m_hud->SetScore(m_foodEatenCount);
            m_moveDelay += sf::seconds(1.0f);
            m_slowTimer = m_slowDuration;

            delete m_foodPoison;
            m_foodPoison = nullptr;
        }

        // Self-collision check
        if (m_snake->CheckSelfCollision()) {
            m_currentState = GameState::GameOver;
            std::cout << "Game Over! Snake collided with itself." << std::endl;
        }
    }
}

void Game::Render() {
    m_window.clear(sf::Color::Black);

    if (m_grid) m_grid->Render(m_window);
    if (m_foodNormal) m_foodNormal->Render(m_window);
    if (m_foodPoison) m_foodPoison->Render(m_window);
    if (m_snake) m_snake->Render(m_window);
    if (m_hud) m_hud->Render(m_window);

    if (m_currentScreen) m_currentScreen->Render(m_window);

    m_window.display();
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

void Game::SwitchToScreen(std::unique_ptr<BaseScreen> newScreen) {
    m_currentScreen = std::move(newScreen);
}
