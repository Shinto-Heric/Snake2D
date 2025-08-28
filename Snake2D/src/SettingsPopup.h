#pragma once
#include "PopupBase.h"
#include "Button.h"
#include <vector>

class SettingsPopup : public PopupBase {
private:
    std::vector<Button> m_buttons;

public:
    SettingsPopup();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
