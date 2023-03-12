#include "StaticArray.h"
#include <iostream>
#include "utils.h"

StaticArray::StaticArray() {
	bgPath = "resources/StaticArray-Background.png";

}

void StaticArray::display(RenderWindow& window, Event &event, int& displayMode) {
	Texture bgTexture;
	bgTexture.loadFromFile(bgPath);
	Sprite bg(bgTexture);
	
	Font font;
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");

	Text back;
	back.setFont(font);
	back.setString("<");
	back.setCharacterSize(20);
	back.setFillColor(Color::White);
	back.setPosition(19.f, 13.f);

	Vector2i mousePos;

	if (event.type == Event::MouseMoved)
		mousePos = Mouse::getPosition(window);

	if (utils::isHover(back, mousePos)){
		back.setFillColor(Color(255, 153, 0));

	}

	if (event.type == Event::MouseButtonPressed) {
		mousePos = Mouse::getPosition(window);
		if (utils::isHover(back, mousePos))
			displayMode = 0;
	}

	window.draw(bg);
	window.draw(back);
	
}

StaticArray::~StaticArray(){}