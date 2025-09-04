#pragma once
#include "screens/BaseScreen.h"
#include "ui/Button.h"
#include "core/GameConfigManager.h"
#include "core/AssetManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class MainMenuScreen : public BaseScreen {
private:
    GameConfigManager& m_config;
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
