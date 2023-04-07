#include "HomeScreen.h"
#include <iostream>
#include "utils.h"
using namespace sf;
using namespace std;

HomeScreen::HomeScreen(RenderWindow &window) {
	this->bgPath = "resources/HomeScreen-Background.png";
	this->cardPaths = { 
		"resources/cards/static-array-card.png",
		"resources/cards/dynamic-array-card.png",
		"resources/cards/singly-linked-list-card.png",
		"resources/cards/doubly-linked-list-card.png",
		"resources/cards/circular-linked-list.png",
		"resources/cards/queue-card.png",
		"resources/cards/stack-card.png",

	};

	this->cardPositions = { {59.f, 360.f}, {516.f, 360.f} , {973.f, 360.f} };
	
	for (size_t i = 3; i < cardPaths.size(); i++) {
		cardPositions.push_back({ cardPositions[2].x + 457* (i - 2) , cardPositions[2].y});
	}

	this->cardsNum = 7;
	this->viewOption = 0;

}

HomeScreen::HomeScreen(string bgPath, vector<string> cardPaths, 
						vector<Vector2f> cardPositions, RenderWindow &window) {
	this->bgPath = bgPath;
	this->cardPaths = cardPaths;
	this->cardPositions = cardPositions;
	this->viewOption = 0;

}

void HomeScreen::calcHomeView(RenderWindow& window) {
	int xSize = window.getSize().x;
	int ySize = window.getSize().y;

	float xFloat = (float)xSize / window.getSize().x;
	float yFloat = (float)ySize / window.getSize().y;

	homeView.reset(sf::FloatRect(0.f, 0.f, xSize, ySize));
	homeView.setViewport(sf::FloatRect(0.f, 0.f, xFloat, yFloat));
}

vector<Sprite> HomeScreen::drawCards(RenderWindow& window, Event &event, int viewOption) {

	vector<Texture> cardTextures;
	vector<Sprite> cards;
	cards.resize(this->cardsNum);
	cardTextures.resize(this->cardsNum);

	for (size_t i = 0; i < this->cardPaths.size(); i++) {
		if (!cardTextures[i].loadFromFile(this->cardPaths[i])) {
			cout << "Cannot load file " << this->cardPaths[i] << endl;
		}
		
		if (!clickMoveRight && !clickMoveLeft)
			cards[i].setPosition(this->cardPositions[i].x - viewOption * 462, this->cardPositions[i].y);
		else if(clickMoveRight && !clickMoveLeft)
			cards[i].setPosition(this->cardPositions[i].x - max(0, viewOption - 1) * 462, this->cardPositions[i].y);
		else if(clickMoveLeft && !clickMoveRight)
			cards[i].setPosition(this->cardPositions[i].x - min(cardsNum - 3, viewOption + 1) * 462, this->cardPositions[i].y);

		if (clickMoveRight && clock.getElapsedTime().asSeconds() < cardMoveTime) {
				cards[i].move((- 462.f / cardMoveTime)* clock.getElapsedTime().asSeconds(), 0);
		}
		else if (clickMoveRight && !clickMoveLeft) {
			clickMoveRight = false;
			cards[i].setPosition(this->cardPositions[i].x - viewOption * 462, this->cardPositions[i].y);
		}

		if (clickMoveLeft && clock.getElapsedTime().asSeconds() < cardMoveTime) {
			cards[i].move((462.f / cardMoveTime) * clock.getElapsedTime().asSeconds(), 0);
		}
		else if(clickMoveLeft && !clickMoveRight) {
			clickMoveLeft = false;
			cards[i].setPosition(this->cardPositions[i].x - viewOption * 462, this->cardPositions[i].y);
		}

		cards[i].setTexture(cardTextures[i]);

	}

	Vector2i mousePos;

	if (event.type == Event::MouseMoved) {
		mousePos = Mouse::getPosition(window);
	}

	for (size_t i = 0; i < cards.size(); i++) {
		if (utils::isHover(cards[i], mousePos)) {

			cards[i].setScale(1.1f, 1.1f);
			int width = cards[i].getGlobalBounds().width;
			int height = cards[i].getGlobalBounds().height;
			float newPosX = cards[i].getPosition().x - (width * 0.1 / 2.0);
			float newPosY = cards[i].getPosition().y - (height * 0.1 / 2.0);
			cards[i].setPosition(newPosX, newPosY);

			//window.draw(cards[i]);
		}
		window.draw(cards[i]);
	}
	return cards;
}

void HomeScreen::drawBackground(RenderWindow& window) {
	Texture bgTexture;
	bgTexture.loadFromFile(this->bgPath);
	Sprite bg(bgTexture);
	window.draw(bg);
}

vector<Sprite> HomeScreen::getButtons(RenderWindow &window, Event &event, int viewOption) {
	Texture lbutTexture;
	lbutTexture.loadFromFile("resources/buttons/Button Left.png");
	Sprite lbutton(lbutTexture);
	lbutton.setPosition(59.f, 260.f);

	Texture rbutTexture;
	rbutTexture.loadFromFile("resources/buttons/Button Right.png");
	Sprite rbutton(rbutTexture);
	rbutton.setPosition(1235.f, 260.f);
	Vector2i mousePos;

	if (event.type == Event::MouseMoved) {
		mousePos = Mouse::getPosition(window);
	}

	if (viewOption == 0) {
		lbutTexture.loadFromFile("resources/buttons/Button Left - disable.png");
		lbutton.setTexture(lbutTexture);
	}
	else if (utils::isHover(lbutton, mousePos)) {
		lbutTexture.loadFromFile("resources/buttons/Button Left - Selected.png");
		lbutton.setTexture(lbutTexture);
	}
	else{
		lbutTexture.loadFromFile("resources/buttons/Button Left.png");
		lbutton.setTexture(lbutTexture);
	}

	if (viewOption == cardsNum - 3) {
		rbutTexture.loadFromFile("resources/buttons/Button Right - disable.png");
		rbutton.setTexture(rbutTexture);
	}
	else if (utils::isHover(rbutton, mousePos)) {
		rbutTexture.loadFromFile("resources/buttons/Button Right - Selected.png");
		rbutton.setTexture(rbutTexture);
	} 
	else {
		rbutTexture.loadFromFile("resources/buttons/Button Right.png");
		rbutton.setTexture(rbutTexture);
	}
	
	window.draw(lbutton);
	window.draw(rbutton);

	return { lbutton, rbutton };
}

void HomeScreen::display(RenderWindow& window, Event &event, int &displayMode) {
	float moveSpeed = 500.f;
	window.setFramerateLimit(60);


	drawBackground(window);
	
	vector<Sprite> buttons = getButtons(window, event, viewOption);

	vector<Sprite> cards = drawCards(window, event, viewOption);

	if (event.type == Event::MouseButtonPressed) {
		Vector2i mousePos = Mouse::getPosition(window);

		for (size_t i = 0; i < buttons.size(); i++) {
			Sprite button = buttons[i];


			if (utils::isHover(button, mousePos)) {
				// Right Button Pressed
				if (i == 1) {
					clock.restart();
					if (viewOption < cardsNum - 3) {
						viewOption++;
						clickMoveRight = true;
					}
				}// Left Button Pressed
				if (i == 0) {
					clock.restart();
					if (viewOption > 0) {
						viewOption--;
						clickMoveLeft = true;
					}
				}
			}
		}

		for (size_t i = 0; i < cards.size(); i++) {
			Sprite card = cards[i];

			if (utils::isHover(card, mousePos)) {

				displayMode = i + 1;
			}
		}
	}
}



HomeScreen::~HomeScreen(){}
