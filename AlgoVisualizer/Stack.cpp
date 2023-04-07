#include "Stack.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


Stack::Stack() {
	bgPath = "resources/Stack-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void Stack::startSearching(int value) {}

void Stack::stopSearching() {}

void Stack::startDeleting(int index) {}

void Stack::stopDeleting() {}

void Stack::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
}

Stack::~Stack() {}