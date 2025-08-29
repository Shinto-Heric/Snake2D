#include "PopupBase.h"
#include "ScreenManager.h"

PopupBase::PopupBase(const std::string& title)
    : m_title(title)
    , m_config(ConfigManager::GetInstance())
    , m_assets(AssetManager::GetInstance())
{
    // --- Background rectangle ---
    m_bgRect.setSize(sf::Vector2f(600.f, 500.f));
    m_bgRect.setFillColor(sf::Color(50, 50, 50, 220));
    m_bgRect.setOutlineColor(sf::Color::White);
    m_bgRect.setOutlineThickness(2.f);
    m_bgRect.setOrigin(m_bgRect.getSize() / 2.f);
    m_bgRect.setPosition(
        static_cast<float>(m_config.GetWindowWidth()) / 2.f,
        static_cast<float>(m_config.GetWindowHeight()) / 2.f
    );

    // --- Title text ---
    m_titleFont = &m_assets.GetFont("title");
    m_titleText.setFont(*m_titleFont);
    m_titleText.setString(m_title);
    m_titleText.setCharacterSize(36);
    m_titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    m_titleText.setPosition(m_bgRect.getPosition().x, m_bgRect.getPosition().y - m_bgRect.getSize().y / 2.f + 40.f);
    sf::Vector2f popupCenter = m_bgRect.getPosition();
    sf::Vector2f popupSize = m_bgRect.getSize();
    float margin = 20.f;
}

void PopupBase::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    
}

void PopupBase::Update(sf::Time dt) {
   
}

void PopupBase::Render(sf::RenderWindow& window) {
    window.draw(m_bgRect);
    window.draw(m_titleText);
   
}
void PopupBase::ClosePopup() {
    // Default behavior: mark inactive, can be handled by screen manager
    std::cout << "Popup closed: " << m_titleText.getString().toAnsiString() << std::endl;
    ScreenManager::GetInstance().ClosePopup();
}