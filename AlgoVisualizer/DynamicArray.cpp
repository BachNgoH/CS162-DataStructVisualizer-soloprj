#pragma once
#include "DynamicArray.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>
#include "Arrow.h"
#include <fstream>
using namespace std;

DynamicArray::DynamicArray() {
	bgPath = "resources/DynamicArray-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	includeSize = true;
	codeBlock.setFont(font);

}

void DynamicArray::initVisualizing(int& option, int initializeOptions)
{
	option = 0;
	isVisualizing = true;
	clock.restart();
	stopSearching();
	ifstream inputFile("file_io/input.txt");

	switch (initializeOptions) {
		// empty
	case 0:
		arrSize = 0;
		arr.clear();
		break;
		// random
	case 1:
		arrSize = rand() % 5 + 3;
		arr.resize(arrSize);
		for (int i = 0; i < arrSize; i++) {
			arr[i] = rand() % 100;
		}
		break;
		// user defined
	case 2:
		int a;
		arr.clear();
		if (inputFile.is_open()) {
			while (inputFile >> a)
				arr.push_back(a);
		}
		arrSize = arr.size();
		break;
	default:
		break;
	}

}

// ------------------------------------------ INSERT ----------------------------------------------------------- // 
void DynamicArray::startInserting(int index, int value) {
	updating = false;
	insertValue = value;
	insertIndex = index;

	totalInsertStep = arr.size() + 1;

	// Code blocks related
	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "int *newArr = new int[size + 1]";
	codeBlock.codelines[1] = "for(int i = 0; i < size + 1; i++)";
	codeBlock.codelines[2] = "	if(i<index) newArr[i] = arr[i]";
	codeBlock.codelines[3] = "  if(i>index) newArr[i] = arr[i-1]";
	codeBlock.codelines[4] = "  if(i==index) newArr[i] = v";
	codeBlock.codelines[5] = "delete[] arr, arr = newArr";
	codeBlock.codelines[6] = "";


	codeBlock.setSelectedLine(0);

	// Array related
	arrStates.clear();
	arrStates.push_back(arr);

	inserting = true;
	insertStep = 0;
}

void DynamicArray::setCodeBlockInsert() {
	if (insertStep == 0)
		codeBlock.setSelectedLine(0);
	if (insertStep < insertIndex)
		codeBlock.setSelectedLine(1, 2);
	else if (insertStep > insertIndex)
		codeBlock.setSelectedLine(1, 3);
	else if (insertStep == insertIndex)
		codeBlock.setSelectedLine(1, 4);

	if (insertStep >= totalInsertStep - 1)
		codeBlock.setSelectedLine(5);

}

void DynamicArray::insertToArray() {
	if (inserting) {
		if (clock.getElapsedTime().asMilliseconds() >= insertStepTime && !isPaused) {
			if (insertStep < totalInsertStep) {
				// cout << insertStep << endl;
				setCodeBlockInsert();
				insertStep += 1;
				clock.restart();
				if (arrStates.size() <= insertStep)
					arrStates.push_back(arr);

			}
			else if (insertStep == totalInsertStep) {
				// inserting = false;
				insertStep += 1;

				if (arrStates.size() <= insertStep) {
					arr.insert(arr.begin() + insertIndex, insertValue);
					arrSize = arr.size();
					arrStates.push_back(arr);
				}
				else {
					arr = arrStates[insertStep];
					arrSize = arr.size();
				}
			}
		}
	}
}

// ------------------------------------------ SEARCH ----------------------------------------------------------- // 
void DynamicArray::startSearching(int value) {
	updating = false;
	search_value = value;
	option = 0;
	searching = true;
	found = false;
	searchStep = 0;

	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "if size == 0, return NOT_FOUND";
	codeBlock.codelines[1] = "for (int i = 0; i < size; i++)";
	codeBlock.codelines[2] = "  if arr[i] == val";
	codeBlock.codelines[3] = "	  return index";
	codeBlock.codelines[4] = "return NO_FOUND";
	codeBlock.codelines[5] = "";
	codeBlock.codelines[6] = "";

	if (arrSize == 0) {
		codeBlock.setSelectedLine(0);
		stopSearching();
	}
	else {
		codeBlock.setSelectedLine(1);
	}
}

void DynamicArray::stopSearching() {
	searching = false;
	found = false;
	searchStep = 0;
	isPaused = false;

}

void DynamicArray::setCodeBlockSearch() {
	if (searchStep == 0) {
		codeBlock.setSelectedLine(1);
		return;
	}
	if (searchStep < arrSize) {
		if (arr[searchStep] != search_value)
			codeBlock.setSelectedLine(1, 2);
		else
			codeBlock.setSelectedLine(3);
	}
	else
		codeBlock.setSelectedLine(4);

}

void DynamicArray::search() {
	if (searching) {

		if (clock.getElapsedTime().asMilliseconds() >= searchStepTime && !isPaused) {
			if (searchStep < arrSize) {
				if (arr[searchStep] != search_value)
					searchStep += 1;
				else
					found = true;
				clock.restart();
			}
			else
				codeBlock.setSelectedLine(5);
		}

		setCodeBlockSearch();
	}
}

// ------------------------------------------ DELETE ----------------------------------------------------------- // 
void DynamicArray::startDeleting(int index) {
	updating = false;
	deleteIndex = index;
	option = 0;
	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "size == 0: return";
	codeBlock.codelines[1] = "int *newArr = new int[size-1]";
	codeBlock.codelines[2] = "for(int i=0; i < size - 1; i++)";
	codeBlock.codelines[3] = "	if(i < index) newArr[i] = arr[i]";
	codeBlock.codelines[4] = "  if(i >= index) newArr[i] = arr[i - 1]";
	codeBlock.codelines[5] = "delete []arr; arr = newArr";
	codeBlock.codelines[6] = "";

	codeBlock.setSelectedLine(1);
	totalDeleteStep = arr.size() + 1;

	if (arrSize == 0) {
		codeBlock.setSelectedLine(0);
		stopDeleting();
	}

	// Array related
	arrStates.clear();
	arrStates.push_back(arr);

	deleting = true;
	deleteStep = 0;
}

void DynamicArray::stopDeleting() {
	deleting = false;
	deleteIndex = 0;
	deleteStep = 0;
	totalDeleteStep = 0;
	isPaused = false;

}

void DynamicArray::setCodeBlockDelete() {
	if (deleteStep < deleteIndex && deleteStep > 0)
		codeBlock.setSelectedLine(2, 3);
	if (deleteStep >= deleteIndex)
		codeBlock.setSelectedLine(2, 4);
	if (deleteStep >= totalDeleteStep - 1)
		codeBlock.setSelectedLine(5);
}

void DynamicArray::deleteAtIndex() {
	if (deleting) {
		if (clock.getElapsedTime().asMilliseconds() >= deleteStepTime && !isPaused) {
			// cout << deleteStep << endl;
			if (deleteStep < totalDeleteStep) {
				deleteStep += 1;
				if (arrStates.size() <= deleteStep)
					arrStates.push_back(arr);
				setCodeBlockDelete();
			}
			else if (deleteStep == totalDeleteStep) {
				deleteStep += 1;
				if (arrStates.size() <= deleteStep) {
					arr.erase(arr.begin() + deleteIndex);
					arrStates.push_back(arr);
					arrSize = arr.size();
				}
				else {
					arr = arrStates[deleteStep];
					arrSize = arr.size();
				}
				codeBlock.setSelectedLine(-1);
			}
			clock.restart();
		}
	}
}

// ------------------------------------------ ANIMATION ----------------------------------------------------------- // 
void DynamicArray::previousStep() {
	isPaused = true;

	if (searching) {
		searchStep = max(searchStep - 1, 0);
		setCodeBlockSearch();
	}
	else if (inserting) {
		insertStep = max(insertStep - 1, 0);
		setCodeBlockInsert();
		arr = arrStates[insertStep];
		arrSize = arr.size();
	}
	else if (deleting) {
		deleteStep = max(deleteStep - 1, 0);
		setCodeBlockDelete();
		arr = arrStates[deleteStep];
		arrSize = arr.size();
	}
}

void DynamicArray::nextStep() {


	if (searching) {
		if (search_value != arr[searchStep])
			searchStep += 1;
		setCodeBlockSearch();
	}
	else if (inserting) {
		if (insertStep < totalInsertStep) {
			// cout << insertStep << endl;

			setCodeBlockInsert();
			insertStep += 1;
			if (arrStates.size() <= insertStep)
				arrStates.push_back(arr);

			clock.restart();
		}
		else if (insertStep == totalInsertStep) { // if(insertStep == totalInsertStep - 1) {
			// inserting = false;
			insertStep += 1;
			if (mode == InsertOption::HEAD || mode == InsertOption::TAIL)
				codeBlock.setSelectedLine(2);
			else
				codeBlock.setSelectedLine(-1);
			if (arrStates.size() <= insertStep) {
				arrSize += 1;
				arr.insert(arr.begin() + insertIndex, insertValue);
				arrStates.push_back(arr);
			}
			else {
				arr = arrStates[insertStep];
				arrSize = arr.size();
			}
		}
	}
	else if (deleting) {
		if (deleteStep < totalDeleteStep) {
			deleteStep += 1;
			if (arrStates.size() <= deleteStep)
				arrStates.push_back(arr);
			setCodeBlockDelete();
		}
		else if (deleteStep == totalDeleteStep) {
			deleteStep += 1;
			if (arrStates.size() <= deleteStep) {
				arr.erase(arr.begin() + deleteIndex);
				arrStates.push_back(arr);
				arrSize = arr.size();
			}
			else {
				arr = arrStates[deleteStep];
				arrSize = arr.size();
			}
			codeBlock.setSelectedLine(-1);
		}
		clock.restart();
	}
	isPaused = true;
}

// ------------------------------------------ DISPLAY ----------------------------------------------------------- // 

void DynamicArray::startUpdating(int value, int index) {
	arr[index] = value;
	updating = true;
	updateIndex = index;
}

void DynamicArray::stopUpdating() {
	updating = false;
}

void DynamicArray::displayControlOptions(int& option, RenderWindow& window, Event& event) {
	__super::displayControlOptions(option, window, event);
}

void DynamicArray::visualize(RenderWindow& window, Event& event) {
	if (isVisualizing && arrSize > 0) {
		Texture pointerTexture;
		pointerTexture.loadFromFile("resources/blocks/StartPointer.png");
		Sprite pointer;
		pointer.setTexture(pointerTexture);
		pointer.setPosition(Vector2f(130, 284));
		bool showMain = true;
		if (inserting && insertStep == totalInsertStep)
			showMain = false;
		if (deleting && deleteStep == totalDeleteStep)
			showMain = false;

		for (int i = 0; i < arrSize && showMain; i++) {

			Texture blockTexture;
			blockTexture.loadFromFile("resources/blocks/Block-Value.png");
			if (arr[i] == 1000)
				blockTexture.loadFromFile("resources/blocks/Block-NoValue.png");
			if ((searching && searchStep == i) || (updating && updateIndex == i))
				blockTexture.loadFromFile("resources/blocks/Block-Search.png");

			Sprite block;
			block.setTexture(blockTexture);
			block.setPosition(Vector2f(262 + i * 105, 279));
			if (i == 0) {
				int timeStep = clock.getElapsedTime().asMilliseconds();
				Arrow arrow(utils::get4sizesCoords(pointer)[1], utils::get4sizesCoords(block)[0], 5, Color::Black);
				arrow.drawToV2(window, timeStep, false);
			}


			Text value;
			value.setString(to_string(arr[i]));
			if (arr[i] == 1000)
				value.setString("0");

			value.setFillColor(Color::Black);
			if ((searching && searchStep == i) || (updating && i == updateIndex)) {
				value.setFillColor(Color::White);
			}

			value.setPosition(Vector2f(306 + i * 105 - 6 * (arr[i] > 10), 297));
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

		if (inserting && insertStep <= totalInsertStep) {
			for (int i = 0; i <= arrSize; i++) {
				
				Texture blockTexture;
				blockTexture.loadFromFile("resources/blocks/Block-Value.png");
				if (i - 1 >= 0 && arr[i - 1] == 1000)
					blockTexture.loadFromFile("resources/blocks/Block-NoValue.png");
				if (i == insertStep)
					blockTexture.loadFromFile("resources/blocks/Block-Search.png");

				Sprite block;
				block.setTexture(blockTexture);
				block.setPosition(Vector2f(262 + i * 105, 379));
				
				Text value;
				value.setFillColor(Color::Black);
				if (i == insertStep)
					value.setFillColor(Color::White);
				int val; 
				if (i == insertIndex) val = insertValue;
				else if (i < insertIndex) val = arr[i];
				else if (i > insertIndex) val = arr[i - 1];
				if (insertStep < i)
					val = 0;

				value.setString(to_string(val));
				value.setPosition(Vector2f(306 + i * 105 - 6 * (val > 10), 397));

				if (val == 1000)
					value.setString("0");

				if (val == 1000)
					value.setPosition(Vector2f(306 + i * 105, 397));
				
				Font font;
				font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
				value.setFont(font);
				value.setCharacterSize(20);

				if (insertStep == arr.size() + 1) {
					block.move(0, -100 * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f));
					value.move(0, -100 * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f));
				}
				else if (insertStep > arr.size() + 1) {
					block.move(0, -100);
					block.move(0, -100);

				}

				window.draw(block);
				window.draw(value);

				if (i == 0 && insertStep > arr.size()) {
					int timeStep = clock.getElapsedTime().asMilliseconds();
					Arrow arrow(utils::get4sizesCoords(pointer)[1], utils::get4sizesCoords(block)[0], 5, Color::Black);
					arrow.drawToV2(window, timeStep, insertStep == arr.size());
				}
			}
		}
		if (deleting && deleteStep <= totalDeleteStep) {
			for (int i = 0; i < arrSize - 1; i++) {

				Texture blockTexture;
				blockTexture.loadFromFile("resources/blocks/Block-Value.png");
				if (i - 1 >= 0 && arr[i - 1] == 1000)
					blockTexture.loadFromFile("resources/blocks/Block-NoValue.png");
				if (i == deleteStep)
					blockTexture.loadFromFile("resources/blocks/Block-Search.png");

				Sprite block;
				block.setTexture(blockTexture);
				block.setPosition(Vector2f(262 + i * 105, 379));

				Text value;
				value.setFillColor(Color::Black);
				if (i == deleteStep)
					value.setFillColor(Color::White);
				int val;
				
				if (i < deleteIndex) val = arr[i];
				else if (i >= deleteIndex) val = arr[i + 1];
				if (deleteStep < i)
					val = 0;

				value.setString(to_string(val));
				value.setPosition(Vector2f(306 + i * 105 - 6 * (val > 10), 397));

				if (val == 1000)
					value.setString("0");

				if (val == 1000)
					value.setPosition(Vector2f(306 + i * 105, 397));

				Font font;
				font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
				value.setFont(font);
				value.setCharacterSize(20);

				if (deleteStep == arr.size() + 1) {
					block.move(0, -100 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
					value.move(0, -100 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
				}
				else if (deleteStep > arr.size()) {
					block.move(0, -100);
					block.move(0, -100);

				}

				window.draw(block);
				window.draw(value);

				if (i == 0 && deleteStep > arr.size() - 1) {
					int timeStep = clock.getElapsedTime().asMilliseconds();
					Arrow arrow(utils::get4sizesCoords(pointer)[1], utils::get4sizesCoords(block)[0], 5, Color::Black);
					arrow.drawToV2(window, timeStep, deleteStep == arr.size());
				}
			}
		}
	}
}

void DynamicArray::drawCodeCells(RenderWindow& window, Event& event) {

	codeBlock.drawTo(window, event);
}

void DynamicArray::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	insertToArray();
	search();
	drawCodeCells(window, event);
	deleteAtIndex();
}

DynamicArray::~DynamicArray() {}