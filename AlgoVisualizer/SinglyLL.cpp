#include "SinglyLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


SinglyLL::SinglyLL() {
	bgPath = "resources/SinglyLinkedList-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void SinglyLL::startSearching(int value) {}

void SinglyLL::stopSearching() {}

void SinglyLL::startDeleting(int index) {}

void SinglyLL::stopDeleting() {}

void SinglyLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	

}

SinglyLL::~SinglyLL() {}