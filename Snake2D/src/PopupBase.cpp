#include "PopupBase.h"

PopupBase::PopupBase(const std::string& title, bool overlay)
    : m_config(ConfigManager::GetInstance())
    , m_assets(AssetManager::GetInstance())
{
    // Overlay setup
    m_overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_overlay.setSize(sf::Vector2f(static_cast<float>(m_config.GetWindowWidth()),
        static_cast<float>(m_config.GetWindowHeight())));

    // Popup background
    m_popupBg.setFillColor(sf::Color(50, 50, 50, 240));
    m_popupBg.setSize(sf::Vector2f(400.f, 400.f));
    m_popupBg.setOrigin(m_popupBg.getSize() / 2.f);
    m_popupBg.setPosition(static_cast<float>(m_config.GetWindowWidth()) / 2.f,
        static_cast<float>(m_config.GetWindowHeight()) / 2.f);

    // Title
    m_titleFont = &m_assets.GetFont("title");
    m_titleText.setFont(*m_titleFont);
    m_titleText.setString(title);
    m_titleText.setCharacterSize(36);
    m_titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect tBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(tBounds.left + tBounds.width / 2.f,
        tBounds.top + tBounds.height / 2.f);
    m_titleText.setPosition(m_popupBg.getPosition().x,
        m_popupBg.getPosition().y - m_popupBg.getSize().y / 2 + 50.f);
}

void PopupBase::Update(sf::Time dt) {
    float speed = 4.f; // animation speed
    if (m_opening && m_animationProgress < 1.f) {
        m_animationProgress += dt.asSeconds() * speed;
        if (m_animationProgress > 1.f) m_animationProgress = 1.f;
    }

    // Apply scale animation
    float scale = 0.8f + 0.2f * m_animationProgress;
    m_popupBg.setScale(scale, scale);
    m_titleText.setScale(scale, scale);
}

void PopupBase::Render(sf::RenderWindow& window) {
    window.draw(m_overlay);
    window.draw(m_popupBg);
    window.draw(m_titleText);
}
