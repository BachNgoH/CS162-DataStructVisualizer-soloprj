#include "StaticArray.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>

StaticArray::StaticArray() {
	bgPath = "resources/StaticArray-Background.png";
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void StaticArray::search() {

	if (searching) {
		if (clock.getElapsedTime().asMilliseconds() > 1000) {
			if (searchStep < arrSize) {
				if(arr[searchStep] != search_value)
					searchStep += 1;
				clock.restart();
			}
		}
	}
}

void StaticArray::deleteAtIndex() {
	if (deleting) {
		if (clock.getElapsedTime().asMilliseconds() > 1000) {
			if (deleteStep < arrSize)
				deleteStep += 1;
			clock.restart();
		}
	}
}

void StaticArray::visualize(RenderWindow& window, Event& event) {
	
	if (isVisualizing && arrSize > 0) {
		Texture pointerTexture;
		pointerTexture.loadFromFile("resources/blocks/StartPointer.png");

		Sprite pointer;
		pointer.setTexture(pointerTexture);

		pointer.setPosition(Vector2f(130, 284));

		for (int i = 0; i < arrSize; i++) {
			Texture blockTexture;
			blockTexture.loadFromFile("resources/blocks/Block-Value.png");
			if(arr[i] == 1000)
				blockTexture.loadFromFile("resources/blocks/Block-NoValue.png");

			if ((searching && searchStep == i) || (deleting && deleteStep == i)) 
				blockTexture.loadFromFile("resources/blocks/Block-Search.png");

			Sprite block;
			block.setTexture(blockTexture);


			block.setPosition(Vector2f(262 + i * 105, 279));

			if (deleting && deleteStep == i && i >= deleteIndex && i < arrSize - 1) {
				arr[i] = arr[i + 1];
			}
			if (deleting && deleteStep == arrSize) {
				arrSize--;
				arr.resize(arrSize);
				deleting = false;
				deleteStep = 0;
				break;
			}

			Text value;
			value.setString(to_string(arr[i]));
			if (arr[i] == 1000)
				value.setString("0");


			value.setFillColor(Color::Black);
			if ((searching && searchStep == i) || (deleting && deleteStep == i)) {
				value.setFillColor(Color::White);
			}

			value.setPosition(Vector2f(306 + i * 105 - 6*(arr[i] > 10), 297));
			if (arr[i] == 1000)
				value.setPosition(Vector2f(306 + i * 105, 297));

			Font font;
			font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
			value.setFont(font);
			value.setCharacterSize(20);

			window.draw(block);
			window.draw(value);
			
		}

		window.draw(pointer);

	}

}

void StaticArray::startSearching(int value) {
	search_value = value;
	option = 0;
	searching = true;
	searchStep = 0;
}

void StaticArray::stopSearching() {
	searching = false;
	searchStep = 0;
}

void StaticArray::startDeleting(int index) {
	deleting = true;
	deleteIndex = index;
	deleteStep = 0;
}

void StaticArray::stopDeleting(){
	deleting = false;
	deleteIndex = 0;
}

void drawControl(RenderWindow &window, Event &event) {
}

void StaticArray::display(RenderWindow& window, Event &event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	search();
	deleteAtIndex();	
}

StaticArray::~StaticArray(){}