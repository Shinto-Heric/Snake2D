#include "Snake.h"
float DirectionToRotation(Direction dir) {
    switch (dir) {
    case Direction::Up:    return -90.f;  // sprite points right by default
    case Direction::Right: return 0.f;
    case Direction::Down:  return 90.f;
    case Direction::Left:  return 180.f;
    }
    return 0.f; // fallback
}
// -------------------------
// Constructor
// -------------------------
Snake::Snake(int gridWidth, int gridHeight, int cellSize, sf::Texture* headTex, sf::Texture* bodyTex)
    : m_gridWidth(gridWidth), m_gridHeight(gridHeight), m_cellSize(cellSize)
{
    // --- Head ---
    m_head.SetTexture(headTex);
    m_head.SetCellSize(cellSize);
    m_head.SetGridPosition({ gridWidth / 2, gridHeight / 2 });
    m_nextDirection = m_currentDirection;
    // --- Body ---
    for (int i = 1; i <= 3; ++i) {
        Entity segment;
        segment.SetTexture(bodyTex);
        segment.SetCellSize(cellSize);
        segment.SetGridPosition({ (gridWidth / 2) - i, gridHeight / 2 });
        m_body.push_back(segment);
    }

    m_currentDirection = Direction::Right;
    m_bodyTexture = bodyTex;
}

// -------------------------
// Direction control
// -------------------------
void Snake::SetDirection(Direction dir) {
    // Prevent reversing into itself
    if ((m_currentDirection == Direction::Up && dir != Direction::Down) ||
        (m_currentDirection == Direction::Down && dir != Direction::Up) ||
        (m_currentDirection == Direction::Left && dir != Direction::Right) ||
        (m_currentDirection == Direction::Right && dir != Direction::Left))
    {
        m_nextDirection = dir; // queue it for next move
    }
}

void Snake::SetBodyTexture(sf::Texture* texture) { m_bodyTexture = texture; }

// -------------------------
// Move snake
// -------------------------
void Snake::Move() {
    // Apply queued direction
    m_currentDirection = m_nextDirection;

    // Move body segments from tail to head
    if (!m_body.empty()) {
        for (int i = static_cast<int>(m_body.size()) - 1; i > 0; --i)
            m_body[i].SetGridPosition(m_body[i - 1].GetGridPosition());
        m_body[0].SetGridPosition(m_head.GetGridPosition()); // first segment follows head
    }

    // Move head
    sf::Vector2i newPos = m_head.GetGridPosition();
    switch (m_currentDirection) {
    case Direction::Up:    newPos.y -= 1; break;
    case Direction::Down:  newPos.y += 1; break;
    case Direction::Left:  newPos.x -= 1; break;
    case Direction::Right: newPos.x += 1; break;
    }

    // Wrap around grid
    if (newPos.x < 0) newPos.x = m_gridWidth - 1;
    if (newPos.x >= m_gridWidth) newPos.x = 0;
    if (newPos.y < 0) newPos.y = m_gridHeight - 1;
    if (newPos.y >= m_gridHeight) newPos.y = 0;

    m_head.SetGridPosition(newPos);
    UpdateHeadRotation();
}

// -------------------------
// Rotate head based on direction
// -------------------------
void Snake::UpdateHeadRotation() {
    m_head.GetSprite().setRotation(DirectionToRotation(m_currentDirection));
}


// -------------------------
// Grow snake
// -------------------------
void Snake::Grow() {
    Entity newSegment;
    newSegment.SetTexture(m_bodyTexture);
    newSegment.SetCellSize(m_cellSize);
    newSegment.SetGridPosition(m_body.empty() ? m_head.GetGridPosition() : m_body.back().GetGridPosition());
    m_body.push_back(newSegment);
}

// -------------------------
// Self-collision check
// -------------------------
bool Snake::CheckSelfCollision() const {
    for (const auto& segment : m_body)
        if (segment.GetGridPosition() == m_head.GetGridPosition())
            return true;
    return false;
}

// -------------------------
// Render snake
// -------------------------
void Snake::Render(sf::RenderWindow& window) {
    m_head.Render(window);

    for (auto& segment : m_body)
        segment.Render(window);
}
std::vector<sf::Vector2i> Snake::GetOccupiedPositions() const {
    std::vector<sf::Vector2i> positions;

    // Head position
    positions.push_back(m_head.GetGridPosition());

    // Body positions
    for (const auto& segment : m_body)
        positions.push_back(segment.GetGridPosition());

    return positions;
}
sf::Vector2i Snake::GetHeadPosition() const {
    return m_head.GetGridPosition();
}
void Snake::Shrink(int segments) {
    while (segments-- > 0 && !m_body.empty())
        m_body.pop_back();
}

void Snake::SetNextDirection(Direction dir) {
    // Prevent reversing into itself
    if ((m_currentDirection == Direction::Up && dir != Direction::Down) ||
        (m_currentDirection == Direction::Down && dir != Direction::Up) ||
        (m_currentDirection == Direction::Left && dir != Direction::Right) ||
        (m_currentDirection == Direction::Right && dir != Direction::Left))
    {
        m_nextDirection = dir; // queue it for next move
    }
}