#include "StaticArray.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>

StaticArray::StaticArray() {
	bgPath = "resources/StaticArray-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	codeBlock.setFont(font);
}

void StaticArray::initVisualizing(int& option) {
	option = 0;
	inserting = false;
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

			if(inserting && i == arr.size() - insertStep + 1)
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
			if ((searching && searchStep == i) || (deleting && deleteStep == i) || (inserting && i == arr.size() - insertStep + 1)) {
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

void StaticArray::previousStep() {
	if (inserting) {
		isPaused = true;
		insertStep = max(insertStep - 1, 0);
		arr = arrStates[insertStep + 1];
		setCodeBlockInsert();
	}
}

void StaticArray::nextStep() {
	if (inserting) {
		if (insertStep <= arr.size() - insertIndex) {
			insertStep += 1;
			isPaused = true;
			setCodeBlockInsert();

			if (arrStates.size() <= insertStep + 1) {
				if (insertStep == 0) {
					arr.resize(arr.size() + 1);
					arrSize = arr.size();
					arrStates.push_back(arr);
				}
				else if (insertStep < arr.size() - insertIndex) {
					arr[arr.size() - insertStep] = arr[arr.size() - insertStep - 1];
					arrStates.push_back(arr);
				}
				else if (insertStep == arr.size() - insertIndex) {
					arr[insertIndex] = insertValue;
					arrStates.push_back(arr);
				}
			}
			else {
				arr = arrStates[insertStep + 1];
				arrSize = arr.size();
			}
		}
	}
}

// --------------------------------- INSERT -----------------------------------------------
void StaticArray::startInserting(int index, int value) {
	stopUpdating();
	insertValue = value;
	insertIndex = index;

	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "size++";
	codeBlock.codelines[1] = "for(k = size; k > index; k++)";
	codeBlock.codelines[2] = "	arr[k] = arr[k - 1]";
	codeBlock.codelines[3] = "arr[index] = value";
	
	codeBlock.setSelectedLine(0);
	// Array related
	arrStates.clear();
	arrStates.push_back(arr);
	clock.restart();
	
	inserting = true;
	insertStep = 0;
}

void StaticArray::setCodeBlockInsert() {
	if (insertStep > 0 && insertStep < arr.size() - insertIndex) {
		codeBlock.setSelectedLine(1, 2);
	}
	else if (insertStep >= arr.size() - insertIndex)
		codeBlock.setSelectedLine(3);
}

void StaticArray::insertToArray() {
	if (inserting) {
		if (clock.getElapsedTime().asMilliseconds() >= insertStepTime && !isPaused) {
			
			if (insertStep <= arr.size() - insertIndex) {
				setCodeBlockInsert();
				if (arrStates.size() <= insertStep + 1) {
					if (insertStep == 0) {
						arr.resize(arr.size() + 1);
						arrSize = arr.size();
						arrStates.push_back(arr);
					}
					else if (insertStep < arr.size() - insertIndex) {
						arr[arr.size() - insertStep] = arr[arr.size() - insertStep - 1];
						arrStates.push_back(arr);
					}
					else if (insertStep == arr.size() - insertIndex) {
						arr[insertIndex] = insertValue;
						arrStates.push_back(arr);
					}
				}
				else {
					arr = arrStates[insertStep + 1];
					arrSize = arr.size();
				}

				insertStep += 1;
			}
			
			clock.restart();
		}
	}
}

void StaticArray::drawCodeCells(RenderWindow& window, Event& event) {

	codeBlock.drawTo(window, event);
}

void StaticArray::display(RenderWindow& window, Event &event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	search();
	drawCodeCells(window, event);
	deleteAtIndex();	
	insertToArray();

}

StaticArray::~StaticArray(){}