#pragma once
#include "SFML/Graphics.hpp"
#include "utils.h"
#include <vector>
#include <string>
using namespace sf;
using namespace std;

class CodeCell {
private:
	Color bgColor = Color(90, 184, 208);
	Color codeColor = Color::White;
	int selectedLine = -1;
	int selectedLine2 = -1;
	Font font;
	bool isOpen = false;
	int cnt = 10;

public:
	vector<string> codelines;

	CodeCell() {
		vector<string> codelines;
		codelines.resize(7);
		for (int i = 0; i < codelines.size(); i++) {
			codelines[i] = "";
		}
		this->codelines = codelines;
	};
	CodeCell(Color bgColor, Color codeColor) {
		this->bgColor = bgColor;
		this->codeColor = codeColor;
		vector<string> codelines;
		codelines.resize(7);
		for (int i = 0; i < codelines.size(); i++) {
			codelines [i] = "";
		}
		this->codelines = codelines;
	}


	void setSelectedLine(int line) {
		selectedLine = line;
		selectedLine2 = -1;
	}
	void setSelectedLine(int line1, int line2) {
		selectedLine = line1;
		selectedLine2 = line2;
	}

	void setFont(Font font) {
		this->font = font;
	}

	void setIsOpen(bool open) {
		isOpen = open;
	}


	void drawTo(RenderWindow& window, Event &event) {
		cnt++;
		RectangleShape controlButton;
		controlButton.setSize(Vector2f(461, 34));
		controlButton.setFillColor(bgColor);
		controlButton.setPosition(960, 890);

		if (event.type == Event::MouseButtonReleased) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (utils::isHover(controlButton, mousePos) && cnt >= 10) {
				isOpen = !isOpen;
				cnt = 0;
			}
		}

		
		float triangleSide = 10;
		ConvexShape controlTriangle(3);
		controlTriangle.setFillColor(codeColor);

		if (isOpen) {
			controlTriangle.setPoint(0, sf::Vector2f(triangleSide / 2, -triangleSide * sqrt(3) / 6));
			controlTriangle.setPoint(1, sf::Vector2f(-triangleSide / 2, -triangleSide * sqrt(3) / 6));
			controlTriangle.setPoint(2, sf::Vector2f(0, triangleSide * sqrt(3) / 3));
		}
		else {
			controlTriangle.setPoint(0, sf::Vector2f(triangleSide / 2, triangleSide * sqrt(3) / 6));
			controlTriangle.setPoint(1, sf::Vector2f(-triangleSide / 2, triangleSide * sqrt(3) / 6));
			controlTriangle.setPoint(2, sf::Vector2f(0, -triangleSide * sqrt(3) / 3));
		}
		controlTriangle.setPosition(Vector2f( controlButton.getPosition().x + controlButton.getGlobalBounds().width / 2.f,
			controlButton.getPosition().y + controlButton.getGlobalBounds().height / 2.f ));

		window.draw(controlButton);
		window.draw(controlTriangle);

		if (isOpen) {
			RectangleShape mainBackground;
			mainBackground.setFillColor(bgColor);
			mainBackground.setSize(Vector2f(461, 286));
			mainBackground.setPosition(960, 586);
			window.draw(mainBackground);

			for (size_t i = 0; i < codelines.size(); i++) {
				Text code;
				code.setFillColor(codeColor);
				code.setFont(font);
				code.setCharacterSize(20);
				code.setPosition(972, 592 + i * 38);
				code.setString(codelines[i]);


				RectangleShape cellBG;
				if (selectedLine == i || selectedLine2 == i)
					cellBG.setFillColor(Color::Black);
				else
					cellBG.setFillColor(bgColor);

				cellBG.setSize(Vector2f(461, 38));
				cellBG.setPosition(960, 586 + i * 38);

				window.draw(cellBG);
				window.draw(code);
			}
		}
	}
};