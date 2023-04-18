#include "Arrow.h"
using namespace sf;

Arrow::Arrow() {
    this->startPosition = Vector2f(0, 0);
    this->endPosition = Vector2f(0, 0);
    this->thickness = 5;
    this->color = Color::Black;
}

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

void Arrow::drawToV2(RenderWindow& window, int timeStep, bool animating) {
    // Calculate the length of the line
    float length = std::sqrt(std::pow(startPosition.x - endPosition.x, 2) + std::pow(endPosition.y - startPosition.y, 2));

    // Calculate the direction of the line
    float direction = std::atan2(endPosition.y - startPosition.y, endPosition.x - startPosition.x);

    // Create the arrow shape m
    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setFillColor(color);
    arrow.setOutlineColor(color);


    arrow.setPoint(0, sf::Vector2f(0, thickness * 1.5));
    arrow.setPoint(1, sf::Vector2f(0, -thickness * 1.5));
    arrow.setPoint(2, sf::Vector2f(thickness * sqrt(3) * 1.5, 0));

    // Rotate the arrow to point in the direction of the line
    arrow.setRotation(direction * 180 / PI);

    // Position the arrow at the end of the line


    // Draw the line 
    Vector2f lineDirection = endPosition - startPosition;
    Vector2f unitDirection = lineDirection / std::sqrt(lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y);
    Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);
    Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    Vector2f arrowOffset = unitDirection * static_cast<float>(thickness * sqrt(3) * 1.5);

    Vector2f timeOffset;
    if (animating && timeStep < animatingTime) {
        if (!isReverse)
            timeOffset = unitDirection * length * (1 - timeStep / animatingTime);
        else
            timeOffset = unitDirection * length * (timeStep / animatingTime);
    }
    endPosition = endPosition - timeOffset;

    arrow.setPosition(endPosition - arrowOffset);


    sf::Vertex line[4];

    line[0].position = startPosition + offset;
    line[1].position = (endPosition - arrowOffset) + offset;
    line[2].position = (endPosition - arrowOffset) - offset;
    line[3].position = startPosition - offset;

    for (int i = 0; i < 4; ++i)
        line[i].color = color;

    window.draw(line, 4, sf::Quads);
    window.draw(arrow);
}

void Arrow::setStartPosition(Vector2f startPosition) {
    this->startPosition = startPosition;
}

void Arrow::setEndPosition(Vector2f endPosition) {
    this->endPosition = endPosition;
}

void Arrow::setAnimatingTime(float animatingTime) {
    this->animatingTime = animatingTime;
}
