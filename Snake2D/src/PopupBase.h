#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

class PopupBase : public BaseScreen {
protected:
    std::string m_title;
    sf::Text m_titleText;
    sf::Font* m_titleFont = nullptr;
    sf::RectangleShape m_bgRect;

    ConfigManager& m_config;
    AssetManager& m_assets;

public:
    PopupBase(const std::string& title);
    // Virtual function to close this popup
    virtual void ClosePopup();
    virtual void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    virtual void Update(sf::Time dt) override;
    virtual void Render(sf::RenderWindow& window) override;
};
