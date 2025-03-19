#include "Grid.h"

Grid::Grid(int spacing) : spacing(spacing), baseColor(100,100,255) {}

void Grid::render(sf::RenderWindow& window, std::vector<Gravity>& gravities) {
    for (int x = 0; x < window.getSize().x; x += spacing) {
        for (int y = 0; y < window.getSize().y; y += spacing) {
            sf::Vector2f force(0, 0);

            // Calculate total force at (x, y)
            for (auto& gravity : gravities) {
                float dx = gravity.get_pos().x - x;
                float dy = gravity.get_pos().y - y;
                float dist = std::sqrt(dx * dx + dy * dy);

                if (dist > 1) { // Avoid division by zero
                    float inverseDist = 1.f / dist;
                    float invSqDropoff = inverseDist * inverseDist;

                    force.x += (dx * gravity.get_strenght() * invSqDropoff);
                    force.y += (dy * gravity.get_strenght() * invSqDropoff);
                }
            }

            // Normalize force direction
            float forceMag = std::sqrt(force.x * force.x + force.y * force.y);
            if (forceMag > 1) {
                force.x /= forceMag;
                force.y /= forceMag;
            }

            // Scale arrow size based on force magnitude
            float arrowSize = std::min(forceMag * 20, 15.0f); // Max arrow size = 15
            sf::Vector2f end(x + force.x * arrowSize, y + force.y * arrowSize);

            // Change color based on force strength
            sf::Color color = baseColor;
            int intensity = std::min(static_cast<int>(forceMag * 500), 255);
            color.r = std::min(100 + intensity, 255);
            color.g = 50;
            color.b = 255 - intensity;

            // Draw arrow (as a line)
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), color),
                sf::Vertex(end, color)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}
