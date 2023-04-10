#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

class utils
{
public:
	bool static isHover(Sprite obj, Vector2i mousePos);
	bool static isHover(Text obj, Vector2i mousePos);
	bool static isHover(RectangleShape obj, Vector2i mousePos);
	Vector2f static getCenterCoords(Vector2f objSize, Vector2f boxSize);
	vector<Vector2f> static get4sizesCoords(Sprite obj);
};



