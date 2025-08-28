#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "ConfigManager.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PopupBase : public BaseScreen {
protected:
    ConfigManager& m_config;
    AssetManager& m_assets;

    sf::RectangleShape m_overlay;      // semi-transparent background
    sf::RectangleShape m_popupBg;      // popup box
    sf::Text m_titleText;
    sf::Font* m_titleFont = nullptr;

    float m_animationProgress = 0.f;   // 0.0 -> 1.0
    bool m_opening = true;              // opening animation flag

public:
    PopupBase(const std::string& title, bool overlay = false);
    virtual ~PopupBase() = default;

    virtual void HandleInput(sf::Event& event, sf::RenderWindow& window) override = 0;
    virtual void Update(sf::Time dt) override;
    virtual void Render(sf::RenderWindow& window) override;
};
