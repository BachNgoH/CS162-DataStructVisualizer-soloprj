#pragma once
#include "SinglyLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>
#include "Arrow.h"
#include <fstream>
using namespace std;



SinglyLL::SinglyLL() {
	bgPath = "resources/SinglyLinkedList-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	includeSize = false;
	codeBlock.setFont(font);

}

void SinglyLL::initVisualizing(int& option, int initializeOptions) 
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

void SinglyLL::startInserting(int index, int value) {
	insertValue = value;
	insertIndex = index;
	if (index == arrSize) {
		mode = InsertOption::TAIL;
		totalInsertStep = 1;

		// Code blocks related
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "Vertex vtx = new Vertex(v)";
		codeBlock.codelines[1] = "tail.next = vtx";
		codeBlock.codelines[2] = "tail = vtx";

		for (int i = 3; i < codeBlock.codelines.size(); i++) {
			codeBlock.codelines[i] = "";
		}
		codeBlock.setSelectedLine(0);
	}
	else if (index == 0) {
		mode = InsertOption::HEAD;
		totalInsertStep = 2;

		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "Vertex vtx = new Vertex(v)";
		codeBlock.codelines[1] = "vtx.next = head";
		codeBlock.codelines[2] = "head = vtx";

		for (int i = 3; i < codeBlock.codelines.size(); i++) {
			codeBlock.codelines[i] = "";
		}

	}
	else {
		mode = InsertOption::INDEX;
		totalInsertStep = index + 4;

		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "Vertex pre = head";
		codeBlock.codelines[1] = "for (k = 0; k < i-1; k++)";
		codeBlock.codelines[2] = "  pre = pre.next";
		codeBlock.codelines[3] = "Vertex aft = pre.next";
		codeBlock.codelines[4] = "Vertex vtx = new Vertext(v)";
		codeBlock.codelines[5] = "vtx.next = aft";
		codeBlock.codelines[6] = "pre.next = vtx";

		codeBlock.setSelectedLine(0);

	}

	// Array related
	arrStates.clear();
	arrStates.push_back(arr);

	inserting = true;
	insertStep = 0;
}

void SinglyLL::drawInsert(int &option) {
	string windowTitle = "Insert To Array";

	RenderWindow addWindow(VideoMode(600, 400), windowTitle, Style::Close | Style::Titlebar);
	vector<string> text = {"Head", "Tail", "Index:", "Value:"};
	vector<Vector2f> positions = { {171,60}, {171,125}, {171,196}, {171,267} };
	vector<Vector2f> textPositions = { {276,74}, {273,136}, {195,207}, {195,278} };
	vector<RectangleShape> boxes;
	vector<Text> allText;
	boxes.resize(text.size());
	allText.resize(text.size());

	for (size_t i = 0; i < text.size(); i++)
	{
		boxes[i].setSize(Vector2f(257, 52));
		boxes[i].setFillColor(Color(217, 217, 217));
		boxes[i].setPosition(positions[i]);

		allText[i].setString(text[i]);
		allText[i].setFont(font);
		allText[i].setCharacterSize(20);
		allText[i].setPosition(textPositions[i]);
		allText[i].setFillColor(Color::Black);
	}

	// Value Box
	TextBox valueTextBox(18, Color::Black, false);
	valueTextBox.setFont(font);
	valueTextBox.setPosition(Vector2f(376, 281));
	valueTextBox.setLimit(true, 1);
	
	RectangleShape valueRect;
	valueRect.setSize(Vector2f(45, 27));
	valueRect.setFillColor(Color(217, 217, 217));
	valueRect.setPosition(365, 280);

	// Index Box
	TextBox indexTextBox(18, Color::Black, false);
	indexTextBox.setFont(font);
	indexTextBox.setPosition(Vector2f(376, 210));
	indexTextBox.setLimit(true, 1);

	RectangleShape indexRect;
	indexRect.setSize(Vector2f(45, 27));
	indexRect.setFillColor(Color(217, 217, 217));
	indexRect.setPosition(365, 209);

	// Done Button
	Texture doneTexture;
	doneTexture.loadFromFile("resources/buttons/DoneButton.png");
	Sprite doneButton;
	doneButton.setTexture(doneTexture);
	doneButton.setPosition(Vector2f(503, 346));

	// Error Message
	Text errorMessage;
	errorMessage.setFont(font);
	errorMessage.setFillColor(Color::Red);
	errorMessage.setCharacterSize(15);
	errorMessage.setPosition(Vector2f(171, 334));


	int addOption = InsertOption::HEAD;

	while (addWindow.isOpen()) {
		Event aevent;
		Vector2i mousePos = Mouse::getPosition(addWindow);

		while (addWindow.pollEvent(aevent)) {
			switch (aevent.type) {
			case Event::Closed:
				addWindow.close();
				option = 0;
				break;
			case Event::TextEntered:
				valueTextBox.typedOn(aevent);
				indexTextBox.typedOn(aevent);
				break;
			case Event::MouseButtonPressed:
				if (utils::isHover(boxes[3], mousePos)) {
					valueTextBox.setSelected(true);
					indexTextBox.setSelected(false);
				}
				else if (utils::isHover(boxes[2], mousePos)) {
					valueTextBox.setSelected(false);
					indexTextBox.setSelected(true);
				}
				else {
					valueTextBox.setSelected(false);
					indexTextBox.setSelected(false);
				}

				if (utils::isHover(doneButton, mousePos)) {
					if (arrSize == 8) {
						errorMessage.setString("The Max Array Size is 8");
					}
					else if (!valueTextBox.isEmpty() && !indexTextBox.isEmpty() && addOption == InsertOption::INDEX) {
						int index = stoi(indexTextBox.getText());
						int value = stoi(valueTextBox.getText());

						if (index >= arrSize || index < 0) {
							//cout << errorMessage.getString().toAnsiString() << endl;
							errorMessage.setString("Invalid index");
						}
						else {
							startInserting(index, value);

							clock.restart();

							stopSearching();
							stopDeleting();

							addWindow.close();
							option = 0;
							isPaused = false;
						}
					}
					else if (!valueTextBox.isEmpty()) {
						mode = addOption;
						insertValue = stoi(valueTextBox.getText());
						if (mode == InsertOption::HEAD)
							startInserting(0, insertValue);
						else {
							startInserting(arrSize, insertValue);
						}

						clock.restart();
						stopSearching();
						stopDeleting();

						addWindow.close();
						option = 0;

					}
					else {
						errorMessage.setString("Value is Required!");
					}
				}
				break;
			default:
				break;
			}
		}

		addWindow.clear(Color(232, 232, 232));

		for (int i = 0; i < text.size(); i++) {

			if (utils::isHover(boxes[i], mousePos) && i != text.size() - 1) {
				boxes[i].setFillColor(Color::Black);
				allText[i].setFillColor(Color::White);
			}
			else {
				boxes[i].setFillColor(Color(217, 217, 217));
				allText[i].setFillColor(Color::Black);
				if (i == text.size() - 1)
					boxes[i].setFillColor(Color(255, 153, 0));
			}

			if (aevent.type == Event::MouseButtonPressed) {
				if (utils::isHover(boxes[i], mousePos) && i != text.size() - 1)
					addOption = i;
			}

			if (addOption == i)
				boxes[i].setFillColor(Color(255, 153, 0));

			addWindow.draw(boxes[i]);
			addWindow.draw(allText[i]);
		}

		if (utils::isHover(doneButton, mousePos)) {
			doneTexture.loadFromFile("resources/buttons/DoneButton_selected.png");
			doneButton.setTexture(doneTexture);
		}
		else {
			doneTexture.loadFromFile("resources/buttons/DoneButton.png");
			doneButton.setTexture(doneTexture);
		}

		addWindow.draw(doneButton);
		addWindow.draw(indexRect); addWindow.draw(valueRect);
		valueTextBox.drawTo(addWindow); indexTextBox.drawTo(addWindow);
		addWindow.draw(errorMessage);

		addWindow.display();
	}
}

void SinglyLL::startSearching(int value) {
	search_value = value;
	option = 0;
	searching = true;
	found = false;
	searchStep = 0;

	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "if empty, return NOT_FOUND";
	codeBlock.codelines[1] = "index = 0, temp = head";
	codeBlock.codelines[2] = "while (temp.item != v)";
	codeBlock.codelines[3] = "  index++, temp = temp.next";
	codeBlock.codelines[4] = "  if temp == null";
	codeBlock.codelines[5] = "    return NOT_FOUND";
	codeBlock.codelines[6] = "return index";


	if (arrSize == 0) {
		codeBlock.setSelectedLine(0);
		stopSearching();
	}
	else {
		codeBlock.setSelectedLine(1);
	}
}

void SinglyLL::stopSearching() {
	searching = false;
	found = false;
	searchStep = 0;
	isPaused = false;

}

void SinglyLL::startDeleting(int index) {
	deleteIndex = index;
	option = 0;
	if (deleteIndex == 0) {
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "temp = head";
		codeBlock.codelines[2] = "head = head.next";
		codeBlock.codelines[3] = "delete temp";
		for (size_t i = 4; i < codeBlock.codelines.size(); i++) {
			codeBlock.codelines[i] = "";
		}

		codeBlock.setSelectedLine(1);
		mode = InsertOption::HEAD;
		totalDeleteStep = 2;
	}
	else if (deleteIndex == arrSize - 1) {

		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "Vertext pre = head, temp = pre.next";
		codeBlock.codelines[2] = "while (temp && temp.next != null)";
		codeBlock.codelines[3] = "  pre = pre.next";
		codeBlock.codelines[4] = "  temp = temp.next";
		codeBlock.codelines[5] = "pre.next = null";
		codeBlock.codelines[6] = "delete temp, tail = pre";

		mode = InsertOption::TAIL;
		codeBlock.setSelectedLine(1);
		totalDeleteStep = deleteIndex + 2;
	}
	else {
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "Vertext pre = head";
		codeBlock.codelines[2] = "for (k = 0; k < i-1; k++)";
		codeBlock.codelines[3] = "  pre = pre.next";
		codeBlock.codelines[4] = "Vertex del = pre.next, aft = del.next";
		codeBlock.codelines[5] = "pre.next = aft // bypass del";
		codeBlock.codelines[6] = "delete del";

		mode = InsertOption::INDEX;
		codeBlock.setSelectedLine(1);
		totalDeleteStep = deleteIndex + 2;
	}

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

void SinglyLL::stopDeleting() {
	deleting = false;
	deleteIndex = 0;
	deleteStep = 0;
	totalDeleteStep = 0;
	isPaused = false;

}

void SinglyLL::previousStep() {
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

void SinglyLL::nextStep() {


	if (searching) {
		if(search_value != arr[searchStep])
			searchStep += 1;
		setCodeBlockSearch();
	}
	else if (inserting) {
		if (insertStep < totalInsertStep ) {
			// cout << insertStep << endl;
			
			setCodeBlockInsert();
			insertStep += 1;
			if(arrStates.size() <= insertStep)
				arrStates.push_back(arr);

			clock.restart();
		}
		else if(insertStep == totalInsertStep) { // if(insertStep == totalInsertStep - 1) {
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
			if(arrStates.size() <= deleteStep)
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

void SinglyLL::setCodeBlockInsert() {
	switch (mode) {
	case (InsertOption::INDEX):
		if (insertStep < insertIndex - 1) {
			codeBlock.setSelectedLine(1, 2);
		}
		else if (insertStep >= insertIndex - 1 && insertStep <= insertIndex) {
			codeBlock.setSelectedLine(3);
		}
		else if (insertStep > insertIndex) {
			codeBlock.setSelectedLine(insertStep - insertIndex + 3);
		}
		break;
	case(InsertOption::HEAD):
		codeBlock.setSelectedLine(insertStep);
		break;
	case(InsertOption::TAIL):
		codeBlock.setSelectedLine(insertStep + 1);
		break;
	}
}

void SinglyLL::insertToArray() {
	if (inserting) {
		if (clock.getElapsedTime().asMilliseconds() >= insertStepTime && !isPaused) {
			if (insertStep < totalInsertStep) {
				// cout << insertStep << endl;
				setCodeBlockInsert();
				insertStep += 1;
				clock.restart();
				if(arrStates.size() <= insertStep)
					arrStates.push_back(arr);

			}
			else if (insertStep == totalInsertStep) {
				// inserting = false;
				insertStep += 1;
				if(mode == InsertOption::HEAD || mode == InsertOption::TAIL)
					codeBlock.setSelectedLine(2);
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

void SinglyLL::setCodeBlockSearch() {
	if (searchStep == 0) {
		codeBlock.setSelectedLine(1);
		return;
	}
	if (searchStep < arrSize) {
		if (arr[searchStep] != search_value)
			codeBlock.setSelectedLine(2, 3);
		else
			codeBlock.setSelectedLine(6);
	}
	else 
		codeBlock.setSelectedLine(5);
	
}

void SinglyLL::search() {
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

void SinglyLL::setCodeBlockDelete() {
	if (mode == InsertOption::HEAD) {
		if (deleteStep == 1)
			codeBlock.setSelectedLine(2);
		if (deleteStep == 2)
			codeBlock.setSelectedLine(3);
	}
	else if (mode == InsertOption::TAIL || mode == InsertOption::INDEX) {
		if (deleteStep < deleteIndex && deleteStep > 0) {
			codeBlock.setSelectedLine(2, 3);
		}
		else if (deleteStep >= deleteIndex && deleteStep <= deleteIndex + 1)
			codeBlock.setSelectedLine(5);
		else if (deleteStep >= deleteIndex + 2)
			codeBlock.setSelectedLine(6);
	}
}

void SinglyLL::deleteAtIndex() {
	if (deleting) {
		if (clock.getElapsedTime().asMilliseconds() >= deleteStepTime && !isPaused) {
			// cout << deleteStep << endl;
			if (deleteStep < totalDeleteStep) {
				deleteStep += 1;
				if(arrStates.size() <= deleteStep)
					arrStates.push_back(arr);
				setCodeBlockDelete();
			}
			else if(deleteStep == totalDeleteStep) {
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

void SinglyLL::displayControlOptions(int& option, RenderWindow& window, Event& event) {
	__super::displayControlOptions(option, window, event);
}

void SinglyLL::visualize(RenderWindow &window, Event &event) {

	if (isVisualizing) {
		vector<Sprite> allLLBlocks;
		allLLBlocks.resize(arr.size());
		// Draw Linked List Blocks
		for (int i = 0; i < arr.size(); i++) {
			
			Texture textureLL;
			textureLL.loadFromFile("resources/blocks/LinkedList.png");
			allLLBlocks[i].setTexture(textureLL);
			allLLBlocks[i].setPosition(Vector2f(127 + 160 * i, 250));
			
			Text value;
			value.setCharacterSize(18);
			value.setFont(font);
			value.setPosition(159 + 160*i, 268);
			value.setString(to_string(arr[i]));
			value.setFillColor(Color::Black);
			
			// Insert Logic;
			if (inserting) {
				switch (mode) {
				case InsertOption::HEAD:
					if (insertStep == 0) {
						allLLBlocks[i].move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
						value.move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
					}
					else if(insertStep <= totalInsertStep) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				case InsertOption::INDEX:
					if (((insertStep < insertIndex && insertStep == i) || 
						(insertStep >= insertIndex && i == insertIndex - 1)) &&\
						insertStep <= totalInsertStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep >= insertIndex && i == insertIndex && insertStep <= totalInsertStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep == insertIndex + 1 && i >= insertIndex) {
						allLLBlocks[i].move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
						value.move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
					}
					else if (insertStep > insertIndex + 1 && insertStep <= totalInsertStep && i >= insertIndex) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				default:
					break;
				}
					
			}
			
			// Search Logic
			if (searching) {
				if (i <= searchStep) {
					textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
					allLLBlocks[i].setTexture(textureLL);
				}
				if (arr[i] == search_value && searchStep == i) {
					textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
					allLLBlocks[i].setTexture(textureLL);
				}
			}

			// Delete Logic
			if (deleting) {
				if (mode == InsertOption::INDEX || mode == InsertOption::TAIL) {
					if (i == deleteStep && deleteStep < deleteIndex && deleteStep <= totalDeleteStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (deleteStep >= deleteIndex && deleteStep <= totalDeleteStep) {
						if (deleteStep >= deleteIndex + 2) {
							if (i == deleteIndex)
								continue;
							else if (i > deleteIndex && deleteStep <= totalDeleteStep) {
								allLLBlocks[i].move(-160 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
								value.move(-160 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
							}
							else if(i > deleteIndex) {
								allLLBlocks[i].move(-160, 0);
								value.move(-160, 0);
							}

						}
						if (i == deleteIndex) {
							textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
							allLLBlocks[i].setTexture(textureLL);

							if (mode == InsertOption::INDEX) {
								if (deleteStep == deleteIndex + 1) {
									allLLBlocks[i].move(0, 100.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
									value.move(0, 100.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
								}
								else if (deleteStep > deleteIndex + 1) {
									allLLBlocks[i].move(0, 100.f);
									value.move(0, 100.f);
								}
							}
						}
						if ((i == deleteIndex - 1 || i == deleteIndex + 1) && deleteStep <= totalDeleteStep) {
							textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
							allLLBlocks[i].setTexture(textureLL);
						}
					}
				} 
				else if(mode == InsertOption::HEAD){
					if (i == deleteStep && deleteStep <= 1) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					else if (deleteStep == 1 && i == 0) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					else if (deleteStep == 2 && i > 0) {
						allLLBlocks[i].move(-160.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
						value.move(-160.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
					}
					else if (deleteStep == 2 && i == 0)
						continue;
				}
			}

			window.draw(allLLBlocks[i]);
			window.draw(value);
		}
		// Draw Arrows
		for (int i = 0; i < arrSize - 1; i++) {
			if (inserting && mode == InsertOption::INDEX && insertStep >= totalInsertStep - 2 && 
				insertStep <= totalInsertStep && i == insertIndex - 1)
				continue;
			Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[i])[1];
			Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[i + 1])[0];
			
			Arrow arrow(startPosition, endPosition, 5, Color::Black);
			int timeStep = clock.getElapsedTime().asMilliseconds();

			if (deleting) {
				arrow.setAnimatingTime(deleteStepTime);

				if (mode == InsertOption::INDEX || mode == InsertOption::TAIL) {
					if (deleteStep >= deleteIndex + 1 && deleteStep <= totalDeleteStep) {
						if (deleteStep >= deleteIndex + 2 && i == deleteIndex)
							continue;

						if (i == deleteIndex - 1 && i + 2 < arrSize) {
							arrow.setEndPosition(utils::get4sizesCoords(allLLBlocks[i + 2])[0]);
							arrow.drawToV2(window, timeStep, deleteStep == deleteIndex + 1);
							continue;
						}

						if (mode == InsertOption::TAIL && deleteStep >= deleteIndex + 1 && i == deleteIndex - 1) {
							if (deleteStep == deleteIndex + 2)
								continue;
							arrow.isReverse = true;
							arrow.drawToV2(window, timeStep, true);
							continue;
						}
					}
					arrow.drawToV2(window, timeStep, (i == deleteStep && i < deleteIndex));
				}
				else if (mode == InsertOption::HEAD) {
					if (deleteStep > 1 && i == 0 && deleteStep <= totalDeleteStep)
						continue;
					arrow.drawToV2(window, timeStep, (i == deleteStep && deleteStep == 0));
				
				}
			}
			else if (inserting) {
				if (mode == InsertOption::HEAD)
					arrow.drawToV2(window, timeStep, (insertStep == i && i < insertIndex));
				else if (mode == InsertOption::INDEX)
					arrow.drawToV2(window, timeStep, (insertStep == i && i < insertIndex - 1));
				else
					arrow.drawToV2(window, timeStep, false);
			}
			else if(searching) {
				arrow.drawTo(window, timeStep, !inserting && (searching && searchStep == i && !found));
			}
			else {
				arrow.drawToV2(window, timeStep, false);
			}
		}

		if (inserting) {
			switch (mode) {
			case InsertOption::HEAD:
				if (insertStep >= 1 && insertStep <= totalInsertStep) {
					Texture textureLL;
					textureLL.loadFromFile("resources/blocks/LinkedList.png");
					Sprite llBlock;
					llBlock.setTexture(textureLL);
					llBlock.setPosition(Vector2f(127 + 160 * insertIndex, 250));

					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * insertIndex, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					if (insertStep == 2 && arr.size() > 0) {
						int timeStep = clock.getElapsedTime().asMilliseconds();
						Vector2f startPosition = utils::get4sizesCoords(llBlock)[1];
						Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[0])[0];
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, true);
					}					
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::TAIL:
				if (insertStep >= 0 && insertStep <= totalInsertStep) {
					Texture textureLL;
					textureLL.loadFromFile("resources/blocks/LinkedList.png");
					Sprite llBlock;
					llBlock.setTexture(textureLL);
					llBlock.setPosition(Vector2f(127 + 160 * arrSize, 250));

					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * arrSize, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					if (insertStep == 1 && arrSize > 0) {
						int timeStep = clock.getElapsedTime().asMilliseconds();
						Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[arrSize-1])[1];
						Vector2f endPosition = utils::get4sizesCoords(llBlock)[0];
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, true);
					}
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::INDEX:
				if (insertStep >= insertIndex + 2 && insertStep <= totalInsertStep) {
					// Block
					Texture addedLLTexture;
					addedLLTexture.loadFromFile("resources/blocks/LinkedList.png");
					Sprite addedLLBlock;
					addedLLBlock.setTexture(addedLLTexture);
					addedLLBlock.setPosition(Vector2f(127 + 160 * insertIndex, 250));

					// Value
					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * insertIndex, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					Vector2f startPosition = utils::get4sizesCoords(addedLLBlock)[1];
					Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[insertIndex])[0];
					int timeStep = clock.getElapsedTime().asMilliseconds();

					if (insertStep >= insertIndex + 3) {
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, insertStep == insertIndex + 3);
					}
					window.draw(addedLLBlock);
					window.draw(value);
					if (insertStep == insertIndex + 4) {
						Vector2f startPosition2 = utils::get4sizesCoords(allLLBlocks[insertIndex - 1])[1];
						Vector2f endPosition2 = utils::get4sizesCoords(addedLLBlock)[0];
						Arrow arrow2(startPosition2, endPosition2, 5, Color::Black);
						arrow2.drawTo(window, timeStep, true);
					}
				}
				break;
			default:
				break;
			}
		}

		// Draw Head/Tail
		if (arrSize == 1) {

			Vector2f firstCenter = Vector2f(allLLBlocks[0].getPosition().x + allLLBlocks[0].getGlobalBounds().width / 2,
				allLLBlocks[0].getPosition().y + allLLBlocks[0].getGlobalBounds().height / 2);
			
			Text head("Head/Tail", font, 20);
			head.setFillColor(Color::Red);
			head.setPosition(firstCenter.x - head.getGlobalBounds().width / 2, firstCenter.y + 50);
			window.draw(head);
		}
		else if (arrSize > 1) {
			Vector2f firstCenter = Vector2f(allLLBlocks[0].getPosition().x + allLLBlocks[0].getGlobalBounds().width / 2,
				allLLBlocks[0].getPosition().y + allLLBlocks[0].getGlobalBounds().height / 2);

			Vector2f lastCenter = Vector2f(allLLBlocks[arrSize - 1].getPosition().x + allLLBlocks[arrSize - 1].getGlobalBounds().width / 2,
				allLLBlocks[arrSize - 1].getPosition().y + allLLBlocks[arrSize - 1].getGlobalBounds().height / 2);

			Text head("Head", font, 20);
			head.setFillColor(Color::Red);
			head.setPosition(firstCenter.x - head.getGlobalBounds().width / 2, firstCenter.y + 40);
			
			Text tail("Tail", font, 20);
			tail.setFillColor(Color::Red);
			tail.setPosition(lastCenter.x - tail.getGlobalBounds().width / 2, lastCenter.y + 40);

			window.draw(head);
			window.draw(tail);
		}
	}
}

void SinglyLL::drawCodeCells(RenderWindow &window, Event &event) {

	codeBlock.drawTo(window, event);
}

void SinglyLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	insertToArray();
	search();
	drawCodeCells(window, event);
	deleteAtIndex();
}

SinglyLL::~SinglyLL() {}