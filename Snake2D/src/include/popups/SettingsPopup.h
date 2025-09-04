#pragma once
#include "popups/PopupBase.h"
#include "ui/Button.h"
#include <vector>

class SettingsPopup : public PopupBase {
private:
std::vector<std::unique_ptr<Button>> m_buttons; 
public:
    SettingsPopup();
    ~SettingsPopup();

    void HandleInput(sf::Event& event, sf::RenderWindow& window) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;
    void ClosePopup() override;
    void OpenInstructionPopup();
};
