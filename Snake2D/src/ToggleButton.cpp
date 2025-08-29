#include "ToggleButton.h"

ToggleButton::ToggleButton()
    : m_enabled(true) {}

void ToggleButton::ApplyTexture() {
    if (m_enabled && m_enabledTexture) {
        m_sprite.setTexture(*m_enabledTexture);
    }
    else if (!m_enabled && m_disabledTexture) {
        m_sprite.setTexture(*m_disabledTexture);
    }
}

void ToggleButton::SetTextures(sf::Texture* enabledTex, sf::Texture* disabledTex) {
    m_enabledTexture = enabledTex;
    //SetBackgroundTexture(enabledTex);
    m_disabledTexture = disabledTex;
    ApplyTexture();
}

void ToggleButton::SetEnabled(bool enabled) {
    m_enabled = enabled;
    ApplyTexture();
}

bool ToggleButton::IsEnabled() const {
    return m_enabled;
}

void ToggleButton::Toggle() {
    m_enabled = !m_enabled;
    ApplyTexture();
}

void ToggleButton::Render(sf::RenderWindow& window) {
    sf::Vector2f pos;
    if (m_useAbsolutePosition) {
        pos = m_absolutePosition;
    }
    else {
        // fallback to grid-based positioning
        sf::Vector2u windowSize = window.getSize();
        pos.x = static_cast<float>(windowSize.x) / 2.f;
        pos.y = static_cast<float>(m_gridPosition.y * m_cellSize);
    }


    // Always draw sprite (even if no m_bgTexture set)
    sf::FloatRect bgBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bgBounds.width / 2.f, bgBounds.height / 2.f);
    m_sprite.setPosition(pos);
    window.draw(m_sprite);
}


void ToggleButton::SetToggleCallback(std::function<void(bool)> callback) {
    Button::SetCallback([this, callback]() {
        this->Toggle();
        if (callback) callback(this->IsEnabled());
        });
}
