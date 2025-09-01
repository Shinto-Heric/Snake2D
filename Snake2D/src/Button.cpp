#include "Button.h"
#include "SoundManager.h"

void Button::SetText(const std::string& text, sf::Font* font, unsigned int size) {
    m_font = font;
    m_text.setFont(*m_font);
    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setFillColor(m_idleColor);
}

void Button::SetClickSound(const std::string& sound)
{
    m_clickSound = sound;
}

void Button::SetTextColors(sf::Color idle, sf::Color hover) {
    m_idleColor = idle;
    m_hoverColor = hover;
    m_text.setFillColor(m_idleColor);
}

void Button::SetBackgroundColors(sf::Color idle, sf::Color hover) {
    m_bgIdleColor = idle;
    m_bgHoverColor = hover;
    if (!m_bgTexture) m_sprite.setColor(m_bgIdleColor);
}

void Button::SetCallback(std::function<void()> callback) {
    m_callback = callback;
}

void Button::SetBackgroundTexture(sf::Texture* texture) {
    if (texture) {
        m_bgTexture = texture;
        m_sprite.setTexture(*m_bgTexture);
        m_sprite.setColor(m_bgIdleColor);
    }
}
void Button::SetPosition(const sf::Vector2f& pos) {
    m_useAbsolutePosition = true;
    m_absolutePosition = pos;
}


void Button::HandleInput(sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::FloatRect bounds;
    if (m_sprite.getTexture()) bounds = m_sprite.getGlobalBounds();
    else bounds = m_text.getGlobalBounds();

    bool hovered = bounds.contains(mousePos);

    if (hovered) {
        m_text.setFillColor(m_hoverColor);
        m_sprite.setColor(m_bgHoverColor);

        // Hover = scale up
        m_targetScale = 1.1f;

        // Hold = scale down
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_targetScale = 0.95f;
        }

        // Callback only on release inside button
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
            if (m_callback) {
                SoundManager::GetInstance().PlayEffect(m_clickSound);
                m_callback();
            }
               
        }
    }
    else {
        m_text.setFillColor(m_idleColor);
        m_sprite.setColor(m_bgIdleColor);
        m_targetScale = 1.f;
    }
}

void Button::Update(sf::Time dt) {
    float delta = m_scaleSpeed * dt.asSeconds();
    m_currentScale += (m_targetScale - m_currentScale) * delta;
}

void Button::Render(sf::RenderWindow& window) {
    sf::Vector2f pos;

    if (m_useAbsolutePosition) {
        pos = m_absolutePosition;
    }
    else {
        // original grid-based calculation
        sf::Vector2u windowSize = window.getSize();
        pos.x = static_cast<float>(windowSize.x) / 2.f;
        pos.y = static_cast<float>(m_gridPosition.y * m_cellSize);
    }

    // Background sprite
    if (m_bgTexture) {
        sf::FloatRect bgBounds = m_sprite.getLocalBounds();
        m_sprite.setOrigin(bgBounds.width / 2.f, bgBounds.height / 2.f);
        m_sprite.setPosition(pos);
        m_sprite.setScale(m_currentScale, m_currentScale);   // <-- apply scale
        window.draw(m_sprite);
    }

    // Center text
    if (m_font) {
        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.left + textBounds.width / 2.f,
            textBounds.top + textBounds.height / 2.f);
        m_text.setPosition(pos);
        m_text.setScale(m_currentScale, m_currentScale);    // <-- apply scale
    }

    window.draw(m_text);
}
