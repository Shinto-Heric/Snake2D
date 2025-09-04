#pragma once
#include "popups/PopupBase.h"
#include "ui/Button.h"
#include <vector>

class ExitPopup : public PopupBase {
private:
    std::vector<std::unique_ptr<Button>> m_buttons;

public:
    ExitPopup();
    ~ExitPopup() = default;

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
