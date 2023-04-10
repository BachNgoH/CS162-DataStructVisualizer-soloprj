#include "SinglyLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include "Arrow.h"
#include <string>
using namespace std;



SinglyLL::SinglyLL() {
	bgPath = "resources/SinglyLinkedList-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	includeSize = false;
}

void SinglyLL::initVisualizing(int& option, int initializeOptions) 
{
	option = 0;
	isVisualizing = true;
	clock.restart();
	switch (initializeOptions) {
	// empty
	case 0:
		arrSize = 0;
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
		break;
	default:
		break;
	}

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
	TextBox valueTextBox(18, Color::White, false);
	valueTextBox.setFont(font);
	valueTextBox.setPosition(Vector2f(376, 281));
	valueTextBox.setLimit(true, 1);
	
	RectangleShape valueRect;
	valueRect.setSize(Vector2f(45, 27));
	valueRect.setFillColor(Color(180, 180, 180));
	valueRect.setPosition(365, 280);

	// Index Box
	TextBox indexTextBox(18, Color::White, false);
	indexTextBox.setFont(font);
	indexTextBox.setPosition(Vector2f(376, 210));
	indexTextBox.setLimit(true, 1);

	RectangleShape indexRect;
	indexRect.setSize(Vector2f(45, 27));
	indexRect.setFillColor(Color(180, 180, 180));
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

					if (!valueTextBox.isEmpty() && !indexTextBox.isEmpty() && addOption == InsertOption::INDEX) {
						int index = stoi(indexTextBox.getText());
						int value = stoi(valueTextBox.getText());

						if (index >= arrSize || index < 0) {
							//cout << errorMessage.getString().toAnsiString() << endl;
							errorMessage.setString("Invalid index");
						}
						else {
							insertValue = value;
							insertIndex = index;
							if (index == arrSize - 1) {
								mode = InsertOption::TAIL;
								totalInsertStep = 1;
							}
							else if (index == 0) {
								mode = InsertOption::HEAD;
								totalInsertStep = 2;
							}
							else {
								mode = InsertOption::INDEX;
								totalInsertStep = index + 4;
							}
							inserting = true;
							insertStep = 0;
							clock.restart();
							addWindow.close();
							option = 0;
						}
					}
					else if (!valueTextBox.isEmpty()) {
						mode = addOption;
						insertValue = stoi(valueTextBox.getText());;
						inserting = true;
						if (mode == InsertOption::HEAD) {
							totalInsertStep = 2;
							insertIndex = 0;
						}
						else {
							totalInsertStep = 1;
							insertIndex = -1;
						}
						insertStep = 0;
						clock.restart();
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

void SinglyLL::startSearching(int value) {}

void SinglyLL::stopSearching() {}

void SinglyLL::startDeleting(int index) {}

void SinglyLL::stopDeleting() {}

void SinglyLL::startInserting() {
	if (inserting) {
		if (clock.getElapsedTime().asMilliseconds() >= insertStepTime) {
			if (insertStep < totalInsertStep) {
				// cout << insertStep << endl;
				insertStep += 1;
				clock.restart();
			}
			else {
				inserting = false;
				insertStep = 0;

				arrSize += 1;
				if (insertIndex == -1)
					arr.push_back(insertValue);
				else
					arr.insert(arr.begin() + insertIndex, insertValue);
				
			}
		}
	}
}

void SinglyLL::visualize(RenderWindow &window, Event &event) {

	if (isVisualizing) {
		vector<Sprite> allLLBlocks;
		allLLBlocks.resize(arrSize);
		// Draw Linked List Blocks
		for (int i = 0; i < arrSize; i++) {
			
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
					else {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
				case InsertOption::INDEX:
					if ((insertStep < insertIndex && insertStep == i) || (insertStep >= insertIndex && i == insertIndex - 1)) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep >= insertIndex && i == insertIndex) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep == insertIndex + 1 && i >= insertIndex) {
						allLLBlocks[i].move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
						value.move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
					}
					else if (insertStep > insertIndex + 1 && i >= insertIndex) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				default:
					break;
				}
					
			}

			window.draw(allLLBlocks[i]);
			window.draw(value);
		}
		// Draw Arrows
		for (int i = 0; i < arrSize - 1; i++) {
			if (mode == InsertOption::INDEX && insertStep > insertIndex + 1 && i == insertIndex - 1)
				continue;
			Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[i])[1];
			Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[i + 1])[0];
			Arrow arrow(startPosition, endPosition, 5, Color::Black);
			int timeStep = clock.getElapsedTime().asMilliseconds();
			arrow.drawTo(window, timeStep, !inserting);
		}

		if (inserting) {
			switch (mode) {
			case InsertOption::HEAD:
				if (insertStep >= 1) {
					Texture textureLL;
					textureLL.loadFromFile("resources/blocks/LinkedList.png");
					Sprite llBlock;
					llBlock.setTexture(textureLL);
					llBlock.setPosition(Vector2f(127 + 160, 250));

					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * insertIndex, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					if (insertStep == 2) {
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
				if (insertStep >= 0) {
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

					if (insertStep == 1) {
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
				if (insertStep >= insertIndex + 2) {
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
	}
}

void SinglyLL::display(RenderWindow& window, Event& event, int& displayMode) {
	drawPageLayout(window, event, displayMode);
	visualize(window, event);
	startInserting();
}

SinglyLL::~SinglyLL() {}