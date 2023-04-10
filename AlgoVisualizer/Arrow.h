#include <SFML/Graphics.hpp>

class Arrow {
public:
    Vector2f startPosition;
    Vector2f endPosition;
    float thickness;
    Color color;

    Arrow();
    Arrow(Vector2f startPosition, Vector2f endPosition, float thickness, Color color);
    void drawTo(sf::RenderWindow& window, int timeStep, bool animating);

private:
    sf::VertexArray m_vertices;
};

Arrow::Arrow() {}

Arrow::Arrow(sf::Vector2f startPosition, Vector2f endPosition, float thickness, Color color) {
    this->startPosition = startPosition;
    this->endPosition = endPosition;
    this->thickness = thickness;
    this->color = color;
}

void Arrow::drawTo(sf::RenderWindow& window, int timeStep, bool animating) {

    float side = thickness * 3;
    float triangleHeight = side * sqrt(3) / 2;
    // Draw Horizontal Line 
    RectangleShape horizontalLine;
    float length = abs(endPosition.x - startPosition.x - triangleHeight);
    float height = thickness;

    if (timeStep < 200 && animating)
        length = length / 200 * timeStep;

    horizontalLine.setSize(Vector2f(length, height));
    horizontalLine.setFillColor(color);
    horizontalLine.setPosition(startPosition.x, startPosition.y - height / 2);

    // Draw triangle
    Vector2f center = { startPosition.x + length + triangleHeight / 3, endPosition.y };

    ConvexShape triangle;

    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(center.x - side / 2, center.y + triangleHeight / 3));
    triangle.setPoint(1, sf::Vector2f(center.x + side / 2, center.y + triangleHeight / 3));
    triangle.setPoint(2, sf::Vector2f(center.x, center.y - 2 * triangleHeight / 3));
    triangle.setFillColor(color);

    float angle = 90.f * 3.14159 / 180;

    // rotate each point of the triangle around the center point
    for (int i = 0; i < triangle.getPointCount(); i++) {
        sf::Vector2f position = triangle.getPoint(i);
        float x = position.x - center.x;
        float y = position.y - center.y;
        position.x = x * cos(angle) - y * sin(angle) + center.x;
        position.y = x * sin(angle) + y * cos(angle) + center.y;
        triangle.setPoint(i, position);
    }

    if (length > 0) {
        window.draw(horizontalLine);
        window.draw(triangle);
    }
    
}