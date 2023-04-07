#include "CircularLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


CircularLL::CircularLL() {
	bgPath = "resources/CircularLinkedList-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void CircularLL::startSearching(int value) {}

void CircularLL::stopSearching() {}

void CircularLL::startDeleting(int index) {}

void CircularLL::stopDeleting() {}

void CircularLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
}

CircularLL::~CircularLL() {}