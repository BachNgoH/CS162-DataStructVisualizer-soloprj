#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
using namespace sf;
using namespace std;

class CodeCell {
private:
	Color bgColor = Color(255, 153, 0);
	Color codeColor = Color::Black;

	vector<string> codelines;
	Sprite background;
	int selectedLine = -1;

public:
	CodeCell() {};
	CodeCell(Color bgColor, Color codeColor) {
		this->bgColor = bgColor;
		this->codeColor = codeColor;
	}

	void drawTo(RenderWindow &window) {
		background.setColor(bgColor);
	}
};