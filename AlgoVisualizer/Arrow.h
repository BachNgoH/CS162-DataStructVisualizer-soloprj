#pragma once

#include <SFML/Graphics.hpp>
#define PI 3.14159265358979323846  
using namespace sf;

class Arrow {
public:
    Vector2f startPosition;
    Vector2f endPosition;
    float thickness;
    Color color;
    float animatingTime = 200.f;
    bool isReverse = false;

    Arrow();
    Arrow(Vector2f startPosition, Vector2f endPosition, float thickness, Color color);
    void drawTo(sf::RenderWindow& window, int timeStep, bool animating);
    void drawToV2(sf::RenderWindow& window, int timeStep, bool animating);
    void setStartPosition(Vector2f startPosition);
    void setEndPosition(Vector2f endPosition);
    void setAnimatingTime(float animatingTime);

private:
    sf::VertexArray m_vertices;
};
