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

void Arrow::drawReverseArrow(RenderWindow& window, int timeStep, bool isAnimating) {

    // Draw the line 

    Vector2f endPosition1 = { startPosition.x + 30, startPosition.y };
    Vector2f endPosition2 = { startPosition.x + 30, startPosition.y - 50 };
    Vector2f endPosition3 = { endPosition.x - 30, startPosition.y - 50 };
    Vector2f endPosition4 = { endPosition.x - 30, startPosition.y };

    // Calculate the direction of the line
    float direction = std::atan2(endPosition.y - endPosition4.y, endPosition.x - endPosition4.x);

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



    Vector2f lineDirection = endPosition - startPosition;
    Vector2f unitVertical = lineDirection / std::sqrt(lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y);
    Vector2f unitPerpendicular(-unitVertical.y, unitVertical.x);
    Vector2f offsetHorizontal = (thickness / 2.f) * unitPerpendicular;

    Vector2f offsetVerticle = { -thickness / 2, 0 };
    Vector2f arrowOffset = -unitVertical * static_cast<float>(thickness * sqrt(3) * 1.5);

    // calculate time offset
    float totalLength = 10 * 2 + 50 * 2 + (endPosition2.x - endPosition3.x);

    bool animateArrow4 = timeStep > animatingTime * (60 + (endPosition2.x - endPosition3.x)) / totalLength;
    bool animateArrow5 = timeStep > animatingTime * (110 + (endPosition2.x - endPosition3.x));

    if (isAnimating && timeStep < animatingTime) {
        float speed = totalLength / animatingTime;
        if (timeStep < animatingTime * (10 / totalLength)) {
            Vector2f timeOffset = Vector2f(1, 0) * speed * static_cast<float>(timeStep);
            endPosition1 = startPosition + timeOffset;
        }
        else if (timeStep < animatingTime * (60 / totalLength)) {
            Vector2f timeOffset = Vector2f(0, -1) * speed * (timeStep - animatingTime * (10 / totalLength));
            endPosition2 = endPosition1 + timeOffset;
        }
        else if (timeStep < animatingTime * (60 + (endPosition2.x - endPosition3.x)) / totalLength) {
            Vector2f timeOffset = Vector2f(-1, 0) * speed * (timeStep - animatingTime * (60 / totalLength));
            endPosition3 = endPosition2 + timeOffset;
        }
        else if (timeStep < animatingTime * (110 + (endPosition2.x - endPosition3.x)) / totalLength) {
            Vector2f timeOffset = Vector2f(0, 1) * speed * (timeStep - animatingTime * (60 + (endPosition2.x - endPosition3.x)) / totalLength);
            endPosition4 = endPosition3 + timeOffset;
        }
        else {
            Vector2f timeOffset = Vector2f(1, 0) * speed * (timeStep - animatingTime * (110 + (endPosition2.x - endPosition3.x)));
            endPosition = endPosition - timeOffset;
        }
    }

    Vertex line1[4];
    line1[0].position = startPosition + offsetHorizontal;
    line1[1].position = endPosition1 + offsetHorizontal;
    line1[2].position = endPosition1 - offsetHorizontal;
    line1[3].position = startPosition - offsetHorizontal;

    Vertex line2[4];
    line2[0].position = endPosition1 + offsetVerticle;
    line2[1].position = endPosition2 + offsetVerticle;
    line2[2].position = endPosition2 - offsetVerticle;
    line2[3].position = endPosition1 - offsetVerticle;

    Vertex line3[4];
    line3[0].position = endPosition2 + offsetHorizontal;
    line3[1].position = endPosition3 + offsetHorizontal;
    line3[2].position = endPosition3 - offsetHorizontal;
    line3[3].position = endPosition2 - offsetHorizontal;

    Vertex line4[4];
    line4[0].position = endPosition3 + offsetVerticle;
    line4[1].position = endPosition4 + offsetVerticle;
    line4[2].position = endPosition4 - offsetVerticle;
    line4[3].position = endPosition3 - offsetVerticle;

    Vertex line5[4];
    line5[0].position = endPosition4 + offsetHorizontal;
    line5[1].position = endPosition - arrowOffset + offsetHorizontal;
    line5[2].position = endPosition - arrowOffset - offsetHorizontal;
    line5[3].position = endPosition4 - offsetHorizontal;

    for (int i = 0; i < 4; ++i) {
        line1[i].color = color;
        line2[i].color = color;
        line3[i].color = color;
        line4[i].color = color;
        line5[i].color = color;

    }
    arrow.setPosition(endPosition - arrowOffset);


    window.draw(line1, 4, sf::Quads);
    if (!isAnimating || (isAnimating && timeStep < animatingTime * (10 / totalLength)))
        arrow.setPosition(endPosition1 - arrowOffset);
    if (!isAnimating || (isAnimating && timeStep > animatingTime * (10 / totalLength))) {
        window.draw(line2, 4, sf::Quads);
        arrow.setRotation(90 / PI);
        arrow.setPosition(endPosition2 - arrowOffset);
    }
    if (!isAnimating || (isAnimating && timeStep > animatingTime * (60 / totalLength))){
        window.draw(line3, 4, sf::Quads);
        arrow.setRotation(180 / PI);

        arrow.setPosition(endPosition3 - arrowOffset);
    }
    if (!isAnimating || (isAnimating && animateArrow4)) {
        arrow.setRotation(-90/ PI);

        window.draw(line4, 4, sf::Quads);
        arrow.setPosition(endPosition4 - arrowOffset);
    }
    if (!isAnimating || (isAnimating && animateArrow5)) {
        arrow.setRotation(direction * 180 / PI);

        window.draw(line5, 4, sf::Quads);
        arrow.setPosition(endPosition - arrowOffset);
    }
    
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


