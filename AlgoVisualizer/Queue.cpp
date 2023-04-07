#include "Queue.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


Queue::Queue() {
	bgPath = "resources/Queue-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void Queue::startSearching(int value) {}

void Queue::stopSearching() {}

void Queue::startDeleting(int index) {}

void Queue::stopDeleting() {}

void Queue::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
}

Queue::~Queue() {}