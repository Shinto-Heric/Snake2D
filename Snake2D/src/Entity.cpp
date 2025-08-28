#include "Entity.h"

// -------------------------
// Grid position
// -------------------------
void Entity::SetGridPosition(const sf::Vector2i& pos) {
    m_gridPosition = pos;
    UpdateSpritePosition();
}

sf::Vector2i Entity::GetGridPosition() const {
    return m_gridPosition;
}

// -------------------------
// Texture
// -------------------------
void Entity::SetTexture(sf::Texture* texture) {
    if (texture) {
        m_sprite.setTexture(*texture);

        // Set origin to sprite center
        sf::FloatRect bounds = m_sprite.getLocalBounds();
        m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
}

// -------------------------
// Cell size
// -------------------------
void Entity::SetCellSize(int size) {
    m_cellSize = size;
    UpdateSpritePosition();
}

// -------------------------
// Update position
// -------------------------
void Entity::UpdateSpritePosition() {
    m_sprite.setPosition(
        m_gridPosition.x * m_cellSize + m_cellSize / 2.f,
        m_gridPosition.y * m_cellSize + m_cellSize / 2.f
    );
}

// -------------------------
// Render
// -------------------------
void Entity::Render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}
void Entity::SetSpriteColor(const sf::Color& color) {
    m_sprite.setColor(color);
}