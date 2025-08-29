#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class MainMenuScreen : public BaseScreen {
private:
    ConfigManager& m_config;
    AssetManager& m_assets;
    std::vector<Button> m_buttons;

    sf::Text m_titleText;
    sf::Font* m_titleFont = nullptr;
    float m_titleTime = 0.f;

    void OpenSettingsPopup();

public:
    MainMenuScreen();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
