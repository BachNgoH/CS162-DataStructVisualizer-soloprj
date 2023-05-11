#include "DoublyLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

DoublyLL::DoublyLL() {
	bgPath = "resources/DoublyLinkedList-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	includeSize = false;
	codeBlock.setFont(font);

}

void DoublyLL::initVisualizing(int& option, int initializeOptions)
{
	option = 0;
	isVisualizing = true;
	clock.restart();
	stopSearching();
	stopUpdating();
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

void DoublyLL::startInserting(int index, int value) {
	stopUpdating();

	insertValue = value;
	insertIndex = index;
	if (index == arrSize) {
		mode = InsertOption::TAIL;
		totalInsertStep = 1;

		// Code blocks related
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "Vertex vtx = new Vertex(v)";
		codeBlock.codelines[1] = "tail.next = vtx, vtx.prev = tail";
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
		codeBlock.codelines[2] = "if(head) head.prev = vtx";
		codeBlock.codelines[3] = "head = vtx";

		for (int i = 4; i < codeBlock.codelines.size(); i++) {
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
		codeBlock.codelines[5] = "vtx.next = aft, aft.prev = vtx";
		codeBlock.codelines[6] = "pre.next = vtx, vtx.prev = pre";

		codeBlock.setSelectedLine(0);

	}

	// Array related
	arrStates.clear();
	arrStates.push_back(arr);

	inserting = true;
	insertStep = 0;
}

void DoublyLL::startSearching(int value) {
	stopUpdating();

	inserting = false;
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

void DoublyLL::stopSearching() {
	searching = false;
	found = false;
	searchStep = 0;
	isPaused = false;

}

void DoublyLL::startDeleting(int index) {
	stopUpdating();

	inserting = false;
	deleteIndex = index;
	option = 0;
	if (deleteIndex == 0) {
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "temp = head";
		codeBlock.codelines[2] = "head = head.next";
		codeBlock.codelines[3] = "delete temp";
		codeBlock.codelines[4] = "if (head != null) head.prev = null";
		for (size_t i = 5; i < codeBlock.codelines.size(); i++) {
			codeBlock.codelines[i] = "";
		}

		codeBlock.setSelectedLine(1);
		mode = InsertOption::HEAD;
		totalDeleteStep = 2;
	}
	else if (deleteIndex == arrSize - 1) {

		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "Vertext temp = tail";
		codeBlock.codelines[2] = "tail = tail.prev";
		codeBlock.codelines[3] = "tail.next = null";
		codeBlock.codelines[4] = "delete temp";
		codeBlock.codelines[5] = "";
		codeBlock.codelines[6] = "";

		mode = InsertOption::TAIL;
		codeBlock.setSelectedLine(1);
		totalDeleteStep = 2;
	}
	else {
		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, do nothing";
		codeBlock.codelines[1] = "Vertext pre = head";
		codeBlock.codelines[2] = "for (k = 0; k < i-1; k++)";
		codeBlock.codelines[3] = "  pre = pre.next";
		codeBlock.codelines[4] = "Vertex del = pre.next, aft = del.next";
		codeBlock.codelines[5] = "pre.next = aft, aft.prev = pre";
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

void DoublyLL::stopDeleting() {
	deleting = false;
	deleteIndex = 0;
	deleteStep = 0;
	totalDeleteStep = 0;
	isPaused = false;

}

void DoublyLL::previousStep() {
	isPaused = true;

	if (searching) {
		searchStep = max(searchStep - 1, 0);
		setCodeBlockSearch();
	}
	else if (updating) {
		updateStep = max(updateStep - 1, 0);
		setCodeBlockUpdate();
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

void DoublyLL::nextStep() {


	if (searching) {
		if (search_value != arr[searchStep])
			searchStep += 1;
		setCodeBlockSearch();
	}
	else if (updating) {
		if (updateStep != updateIndex)
			updateStep += 1;
		setCodeBlockUpdate();
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

void DoublyLL::setCodeBlockInsert() {
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
		if (insertStep == 1)
			codeBlock.setSelectedLine(1, 2);
		break;
	case(InsertOption::TAIL):
		codeBlock.setSelectedLine(insertStep + 1);
		break;
	}
}

void DoublyLL::insertToArray() {
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
				if (mode == InsertOption::HEAD)
					codeBlock.setSelectedLine(3);
				else if (mode == InsertOption::TAIL)
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

void DoublyLL::setCodeBlockSearch() {
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

void DoublyLL::search() {
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

void DoublyLL::setCodeBlockDelete() {
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

void DoublyLL::deleteAtIndex() {
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
				codeBlock.setSelectedLine(4);
			}
			clock.restart();
		}
	}
}

void DoublyLL::startUpdating(int value, int index) {
	updateIndex = index;
	updateValue = value;
	option = 0;
	updated = false;
	updateStep = 0;
	updating = true;
	inserting = false;

	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "if empty, return";
	codeBlock.codelines[1] = "temp = head";
	codeBlock.codelines[2] = "for (k = 0; k < i-1; k++)";
	codeBlock.codelines[3] = "  temp = temp.next";
	codeBlock.codelines[4] = "  if temp == null";
	codeBlock.codelines[5] = "    return ";
	codeBlock.codelines[6] = "temp.val = v";


	if (arrSize == 0) {
		codeBlock.setSelectedLine(0);
		stopUpdating();
	}
	else {
		codeBlock.setSelectedLine(1);
	}
	// Array related
	arrStates.clear();
	// arrStates.push_back(arr);
	clock.restart();
}

void DoublyLL::stopUpdating() {
	updating = false;
	updated = false;
	updateStep = 0;
	isPaused = false;
}

void DoublyLL::setCodeBlockUpdate() {
	if (updateStep == 0) {
		codeBlock.setSelectedLine(1);
		return;
	}
	if (updateStep < arrSize) {
		if (updateStep != updateIndex)
			codeBlock.setSelectedLine(2, 3);
		else
			codeBlock.setSelectedLine(6);
	}
	else
		codeBlock.setSelectedLine(5);
}

void DoublyLL::update() {
	if (updating) {
		if (clock.getElapsedTime().asMilliseconds() >= updateTimeStep && !isPaused) {
			if (updateStep < arrSize) {
				if (updateStep < updateIndex) {
					updateStep += 1;
					if (arrStates.size() <= updateStep)
						arrStates.push_back(arr);
				}
				else {
					if (arrStates.size() <= updateStep) {
						arr[updateIndex] = updateValue;
						arrStates.push_back(arr);
						arrSize = arr.size();
					}
					else {
						arr = arrStates[updateStep];
						arrSize = arr.size();
					}
					updated = true;
				}
				clock.restart();
			}
			else
				codeBlock.setSelectedLine(5);
		}
		setCodeBlockUpdate();
	}
}

void DoublyLL::displayControlOptions(int& option, RenderWindow& window, Event& event) {
	__super::displayControlOptions(option, window, event);
}

void DoublyLL::visualize(RenderWindow& window, Event& event) {

	if (isVisualizing) {
		vector<Sprite> allLLBlocks;
		allLLBlocks.resize(arr.size());
		// Draw Linked List Blocks
		for (int i = 0; i < arr.size(); i++) {

			Texture textureLL;
			if (palleteCode == 1)
				textureLL.loadFromFile("resources/blocks/LinkedList-vintage.png");
			else if (palleteCode == 2)
				textureLL.loadFromFile("resources/blocks/LinkedList-warm.png");
			else
				textureLL.loadFromFile("resources/blocks/LinkedList.png");			allLLBlocks[i].setTexture(textureLL);
			allLLBlocks[i].setPosition(Vector2f(127 + 160 * i, 250));

			Text value;
			value.setCharacterSize(18);
			value.setFont(font);
			value.setPosition(159 + 160 * i, 268);
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
					else if (insertStep <= totalInsertStep) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				case InsertOption::INDEX:
					if (((insertStep < insertIndex && insertStep == i) ||
						(insertStep >= insertIndex && i == insertIndex - 1)) && \
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
			
			// Update Logic
			if (updating) {
				if (i == updateStep) {
					textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
					allLLBlocks[i].setTexture(textureLL);
				}
				if (i == updateIndex && updateStep == i) {
					textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
					allLLBlocks[i].setTexture(textureLL);
				}
			}

			// Delete Logic
			if (deleting) {
				if (mode == InsertOption::INDEX) {
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
							else if (i > deleteIndex) {
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
				else if (mode == InsertOption::HEAD) {
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
				else if (mode == InsertOption::TAIL) {
					if (deleteStep >= 0 && i == arr.size() - 1 && deleteStep < 2) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (deleteStep == 1 && i == arr.size() - 2) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					else if (deleteStep == 2 && i == arr.size() - 1)
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

			Vector2f startPosition1 = { startPosition.x, startPosition.y + 10 };
			Vector2f endPosition1 = { endPosition.x, endPosition.y + 10 };

			Vector2f startPosition2 = { startPosition.x, startPosition.y - 10 };
			Vector2f endPosition2 = { endPosition.x, endPosition.y - 10 };

			Arrow arrow1(startPosition1, endPosition1, 5, Color::Black);
			Arrow arrow2(endPosition2, startPosition2, 5, Color::Black);
			
			int timeStep = clock.getElapsedTime().asMilliseconds();

			if (deleting) {
				arrow1.setAnimatingTime(deleteStepTime);
				arrow2.setAnimatingTime(deleteStepTime);

				if (mode == InsertOption::INDEX) {
					if (deleteStep >= deleteIndex + 1 && deleteStep <= totalDeleteStep) {
						if (deleteStep >= deleteIndex + 2 && i == deleteIndex)
							continue;

						if (i == deleteIndex - 1 && i + 2 < arrSize) {
							Vector2f newEndPosition = utils::get4sizesCoords(allLLBlocks[i + 2])[0];
							Vector2f newEndPosition1 = { newEndPosition.x, newEndPosition.y + 10 };
							Vector2f newEndPosition2 = { newEndPosition.x, newEndPosition.y - 10 };

							arrow1.setEndPosition(newEndPosition1);
							arrow1.drawToV2(window, timeStep, deleteStep == deleteIndex + 1);

							arrow2.setStartPosition(newEndPosition2);
							arrow2.drawToV2(window, timeStep, deleteStep == deleteIndex + 1);

							continue;
						}

					}
					arrow1.drawToV2(window, timeStep, (i == deleteStep && i < deleteIndex));
					arrow2.drawToV2(window, timeStep, false);

				}
				else if (mode == InsertOption::HEAD) {
					if (deleteStep > 1 && i == 0 && deleteStep <= totalDeleteStep)
						continue;
					arrow1.drawToV2(window, timeStep, (i == deleteStep && deleteStep == 0));
					arrow2.drawToV2(window, timeStep, (i == deleteStep && deleteStep == 0));
				}
				else if (mode == InsertOption::TAIL) {
					if (deleteStep == 2) {
						arrow1.isReverse = true;
						arrow2.isReverse = true;
						arrow1.drawToV2(window, timeStep, (i == arr.size() - 2));
						arrow2.drawToV2(window, timeStep, (i == arr.size() - 2));
						continue;
					}
					arrow1.drawToV2(window, timeStep, false);
					arrow2.drawToV2(window, timeStep, (deleteStep == 1 && i == arr.size() - 2));
				}
			}
			else if (inserting) {
				if (mode == InsertOption::HEAD) {
					arrow1.drawToV2(window, timeStep, (insertStep == i && i < insertIndex));
					arrow2.drawToV2(window, timeStep, false);
				}
				else if (mode == InsertOption::INDEX) {
					arrow1.drawToV2(window, timeStep, (insertStep == i && i < insertIndex - 1));
					arrow2.drawToV2(window, timeStep, false);

				}
				else {
					arrow1.drawToV2(window, timeStep, false);
					arrow2.drawToV2(window, timeStep, false);

				}
			}
			else if (searching) {
				arrow1.drawToV2(window, timeStep, (searchStep == i && !found && arr[i] != search_value));
				arrow2.drawToV2(window, timeStep, false);

			}
			else if (updating) {
				arrow1.drawToV2(window, timeStep, (updateStep == i && !updated && i != updateIndex));
				arrow2.drawToV2(window, timeStep, false);
			}
			else {
				arrow1.drawToV2(window, timeStep, false);
				arrow2.drawToV2(window, timeStep, false);

			}
		}

		if (inserting) {
			switch (mode) {
			case InsertOption::HEAD:
				if (insertStep >= 1 && insertStep <= totalInsertStep) {
					Texture textureLL;
					if (palleteCode == 1)
						textureLL.loadFromFile("resources/blocks/LinkedList-vintage.png");
					else if (palleteCode == 2)
						textureLL.loadFromFile("resources/blocks/LinkedList-warm.png");
					else
						textureLL.loadFromFile("resources/blocks/LinkedList.png");					Sprite llBlock;
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
						
						Vector2f startPosition1 = { startPosition.x, startPosition.y + 10 };
						Vector2f endPosition1 = { endPosition.x, endPosition.y + 10 };

						Vector2f startPosition2 = { startPosition.x, startPosition.y - 10 };
						Vector2f endPosition2 = { endPosition.x, endPosition.y - 10 };
						
						Arrow arrow1(startPosition1, endPosition1, 5, Color::Black);
						Arrow arrow2(endPosition2, startPosition2, 5, Color::Black);
						
						arrow1.drawToV2(window, timeStep, true);
						arrow2.drawToV2(window, timeStep, true);

					}
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::TAIL:
				if (insertStep >= 0 && insertStep <= totalInsertStep) {
					Texture textureLL;
					if (palleteCode == 1)
						textureLL.loadFromFile("resources/blocks/LinkedList-vintage.png");
					else if (palleteCode == 2)
						textureLL.loadFromFile("resources/blocks/LinkedList-warm.png");
					else
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
						Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[arrSize - 1])[1];
						Vector2f endPosition = utils::get4sizesCoords(llBlock)[0];

						Vector2f startPosition1 = { startPosition.x, startPosition.y + 10 };
						Vector2f endPosition1 = { endPosition.x, endPosition.y + 10 };

						Vector2f startPosition2 = { startPosition.x, startPosition.y - 10 };
						Vector2f endPosition2 = { endPosition.x, endPosition.y - 10 };

						Arrow arrow1(startPosition1, endPosition1, 5, Color::Black);
						Arrow arrow2(endPosition2, startPosition2, 5, Color::Black);

						arrow1.drawToV2(window, timeStep, true);
						arrow2.drawToV2(window, timeStep, true);

					}
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::INDEX:
				if (insertStep >= insertIndex + 2 && insertStep <= totalInsertStep) {
					// Block
					Texture addedLLTexture;
					if (palleteCode == 1)
						addedLLTexture.loadFromFile("resources/blocks/LinkedList-vintage.png");
					else if (palleteCode == 2)
						addedLLTexture.loadFromFile("resources/blocks/LinkedList-warm.png");
					else
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



					int timeStep = clock.getElapsedTime().asMilliseconds();

					if (insertStep >= insertIndex + 3) {
						Vector2f startPosition = utils::get4sizesCoords(addedLLBlock)[1];
						Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[insertIndex])[0];

						Vector2f startPosition1 = { startPosition.x, startPosition.y + 10 };
						Vector2f endPosition1 = { endPosition.x, endPosition.y + 10 };

						Vector2f startPosition2 = { startPosition.x, startPosition.y - 10 };
						Vector2f endPosition2 = { endPosition.x, endPosition.y - 10 };
						
						Arrow arrow1(startPosition1, endPosition1, 5, Color::Black);
						arrow1.drawToV2(window, timeStep, insertStep == insertIndex + 3);

						Arrow arrow2(endPosition2, startPosition2, 5, Color::Black);
						arrow2.drawToV2(window, timeStep, insertStep == insertIndex + 3);
					}
					window.draw(addedLLBlock);
					window.draw(value);
					if (insertStep == insertIndex + 4) {
						Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[insertIndex - 1])[1];
						Vector2f endPosition = utils::get4sizesCoords(addedLLBlock)[0];

						Vector2f startPosition1 = { startPosition.x, startPosition.y + 10 };
						Vector2f endPosition1 = { endPosition.x, endPosition.y + 10 };

						Vector2f startPosition2 = { startPosition.x, startPosition.y - 10 };
						Vector2f endPosition2 = { endPosition.x, endPosition.y - 10 };


						Arrow arrow1(startPosition1, endPosition1, 5, Color::Black);
						arrow1.drawToV2(window, timeStep, true);

						Arrow arrow2(endPosition2, startPosition2, 5, Color::Black);
						arrow2.drawToV2(window, timeStep, true);
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

void DoublyLL::drawCodeCells(RenderWindow& window, Event& event) {
	codeBlock.bgColor = pallete[2];
	codeBlock.drawTo(window, event);
}

void DoublyLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	insertToArray();
	search();
	update();
	drawCodeCells(window, event);
	deleteAtIndex();
}

DoublyLL::~DoublyLL() {}