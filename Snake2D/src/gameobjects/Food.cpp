#include "gameobjects/Food.h"
#include <cstdlib> // for rand()
#include <ctime>

Food::Food(int gridWidth, int gridHeight, sf::Texture* texture, FoodType type)
    : m_gridWidth(gridWidth), m_gridHeight(gridHeight), m_type(type)
{
    SetTexture(texture);
    srand(static_cast<unsigned>(time(nullptr)));
    Respawn({});
}

void Food::Respawn(const std::vector<sf::Vector2i>& occupiedPositions) {
    sf::Vector2i newPos;
    bool collision;
    do {
        collision = false;
        newPos.x = rand() % m_gridWidth;
        newPos.y = rand() % m_gridHeight;

        // Avoid spawning on snake
        for (auto& pos : occupiedPositions) {
            if (pos == newPos) {
                collision = true;
                break;
            }
        }
    } while (collision);

    SetGridPosition(newPos);
}
