#pragma once
#include "BaseScreen.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class MainMenuScreen : public BaseScreen {
private:
    ConfigManager& m_config;
    AssetManager& m_assets;

    sf::Texture* m_bgTexture = nullptr; // Screen background
    sf::Sprite m_bgSprite;

    std::vector<Button> m_buttons;

public:
    MainMenuScreen(ConfigManager& config, AssetManager& assets);

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
