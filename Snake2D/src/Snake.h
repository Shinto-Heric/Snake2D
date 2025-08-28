#pragma once
#include "Entity.h"
#include <vector>

enum class Direction { Up, Down, Left, Right };

class Snake {
private:
    Direction m_currentDirection = Direction::Right;
    Direction m_nextDirection;

    Entity m_head;                    // Snake head
    std::vector<Entity> m_body;       // Body segments

    int m_gridWidth, m_gridHeight;    // Grid boundaries
    int m_cellSize = 32;

    sf::Texture* m_bodyTexture = nullptr;

    void UpdateHeadRotation();
public:
    Snake(int gridWidth, int gridHeight, int cellSize, sf::Texture* headTex, sf::Texture* bodyTex);

    void SetDirection(Direction dir);
    Direction GetDirection() const { return m_currentDirection; }
    void SetBodyTexture(sf::Texture* texture);

    void Move();
    void Grow();
    bool CheckSelfCollision() const;
    std::vector<sf::Vector2i> GetOccupiedPositions() const;
    sf::Vector2i GetHeadPosition() const;
    void Shrink(int segments = 3);
    void Render(sf::RenderWindow& window);
    void SetNextDirection(Direction dir);
};
