#include "gameobjects/Grid.h"

Grid::Grid(int cols, int rows, int cellSize, sf::Texture* texture)
    : m_cols(cols), m_rows(rows), m_cellSize(cellSize), m_texture(texture)
{
    m_cellShape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    if (m_texture)
        m_cellShape.setTexture(m_texture);
    else
        m_cellShape.setFillColor(sf::Color(50, 200, 50)); // Default grass green
}

void Grid::Render(sf::RenderWindow& window) {
    for (int i = 0; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            m_cellShape.setPosition(static_cast<float>(i * m_cellSize),
                static_cast<float>(j * m_cellSize));
            window.draw(m_cellShape);
        }
    }
}
