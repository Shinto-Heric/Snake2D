#include "InstructionPopup.h"
#include "ScreenManager.h"
#include "ConfigManager.h"
#include "AssetManager.h"

InstructionPopup::InstructionPopup()
    : PopupBase("Instructions")
{
    // Font for instructions
    m_font = &AssetManager::GetInstance().GetFont("body");

    // Setup instruction text
    m_instructionText.setFont(*m_font);
    m_instructionText.setCharacterSize(24);
    m_instructionText.setFillColor(sf::Color::White);
    m_instructionText.setString(
        "Use arrow keys or WASD to move.\n"
        "Eat food to grow longer.\n"
        "Avoid poison food - costs 1 life.\n"
        "Don't hit yourself - Game Over."
    );

    // Center text within popup
    sf::Vector2f popupPos = m_bgRect.getPosition();
    sf::Vector2f popupSize = m_bgRect.getSize();
    sf::FloatRect textBounds = m_instructionText.getLocalBounds();
    m_instructionText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    m_instructionText.setPosition(popupPos.x, popupPos.y);

    // Close button

    Button closeButton;
    m_closeButton.SetBackgroundTexture(&m_assets.GetTexture("button_bg"));
    m_closeButton.SetCellSize(32);
    m_closeButton.SetText("Back", &m_assets.GetFont("button"), 24);
    m_closeButton.SetGridPosition({ 5, 17 });
    m_closeButton.SetBackgroundColors(sf::Color(178, 34, 34), sf::Color(220, 20, 60));
    m_closeButton.SetTextColors(sf::Color::White, sf::Color::Yellow);
    m_closeButton.SetCallback([]() {
        ScreenManager::GetInstance().ClosePopup();
        });
}

void InstructionPopup::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    m_closeButton.HandleInput(event, window);
}

void InstructionPopup::Update(sf::Time dt) {
    m_closeButton.Update(dt);
}

void InstructionPopup::Render(sf::RenderWindow& window) {
    PopupBase::Render(window);
    window.draw(m_instructionText);
    m_closeButton.Render(window);
}
