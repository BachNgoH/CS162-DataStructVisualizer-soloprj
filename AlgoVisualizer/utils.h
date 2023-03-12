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

};

