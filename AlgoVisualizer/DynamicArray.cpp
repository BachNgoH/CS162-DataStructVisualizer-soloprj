#include "DynamicArray.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


DynamicArray::DynamicArray() {
	bgPath = "resources/DynamicArray-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void DynamicArray::startSearching(int value) {}

void DynamicArray::stopSearching() {}

void DynamicArray::startDeleting(int index) {}

void DynamicArray::stopDeleting() {}

void DynamicArray::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
}

DynamicArray::~DynamicArray() {}