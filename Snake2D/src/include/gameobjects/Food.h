#pragma once
#include "core/Entity.h"
#include <SFML/Graphics.hpp>
enum class FoodType {
    Normal,
    Poison
};

class Food : public Entity {
private:
    int m_gridWidth;
    int m_gridHeight;
    FoodType m_type;
public:
    Food(int gridWidth, int gridHeight, sf::Texture* texture, FoodType type = FoodType::Normal);

    FoodType GetType() const { return m_type; }
    void SetType(FoodType type) { m_type = type; }

    void Respawn(const std::vector<sf::Vector2i>& occupiedPositions);
};
