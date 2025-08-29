#pragma once
#include "PopupBase.h"
#include "Button.h"
#include <vector>

class InstructionPopup : public PopupBase {
private:
    Button m_closeButton;
    sf::Text m_instructionText;
    sf::Font* m_font = nullptr;

public:
    InstructionPopup();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
};
