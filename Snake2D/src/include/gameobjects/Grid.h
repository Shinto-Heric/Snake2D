#pragma once
#include <SFML/Graphics.hpp>

class Grid {
private:
    int m_cols;
    int m_rows;
    int m_cellSize;

    sf::RectangleShape m_cellShape; // Reusable shape
    sf::Texture* m_texture;         // Optional tile texture, can be nullptr
public:
    Grid(int cols, int rows, int cellSize, sf::Texture* texture = nullptr);

    void Render(sf::RenderWindow& window);
};
