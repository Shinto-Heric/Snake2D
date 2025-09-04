#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Vector2i m_gridPosition; // Position on the grid
    sf::Sprite m_sprite;
    int m_cellSize = 32;         // Default, but configurable

    void UpdateSpritePosition();

public:
    Entity() = default;
    virtual ~Entity() = default;

    void SetGridPosition(const sf::Vector2i& pos);
    sf::Vector2i GetGridPosition() const;

    void SetTexture(sf::Texture* texture);
    void SetCellSize(int size);

    virtual void Render(sf::RenderWindow& window);
    sf::Sprite& GetSprite() { return m_sprite; }

    void SetSpriteColor(const sf::Color& color);
};
