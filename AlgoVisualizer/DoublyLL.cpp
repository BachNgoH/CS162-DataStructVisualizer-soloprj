#include "DoublyLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


DoublyLL::DoublyLL() {
	bgPath = "resources/DoublyLinkedList-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void DoublyLL::startSearching(int value) {}

void DoublyLL::stopSearching() {}

void DoublyLL::startDeleting(int index) {}

void DoublyLL::stopDeleting() {}

void DoublyLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
}

DoublyLL::~DoublyLL() {};