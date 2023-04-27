#include "Stack.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>


Stack::Stack() {
	bgPath = "resources/Stack-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	controlOptions = { "Initialize", "Push", "Pop", "Peak", "Clear"};
}

void Stack::startPushing(int value) {
	insertValue = value;
	insertIndex = 0;

	mode = InsertOption::HEAD;
	totalInsertStep = 2;

	codeBlock.setIsOpen(true);
	codeBlock.codelines[0] = "Vertex vtx = new Vertex(v)";
	codeBlock.codelines[1] = "vtx.next = head";
	codeBlock.codelines[2] = "head = vtx";

	for (int i = 3; i < codeBlock.codelines.size(); i++) {
		codeBlock.codelines[i] = "";
	}
	// Array related
	arrStates.clear();
	arrStates.push_back(arr);

	inserting = true;
	insertStep = 0;
}

void Stack::drawPush(int& option) {
	RenderWindow pushWindow(VideoMode(600, 400), "Push", Style::Titlebar | Style::Close);
	Texture bgTexture;
	bgTexture.loadFromFile("resources/backgrounds/Push-bg.png");
	Sprite pushBg;
	pushBg.setTexture(bgTexture);

	// Done Button
	Texture doneTexture;
	doneTexture.loadFromFile("resources/buttons/DoneButton.png");

	Sprite doneButton;
	doneButton.setTexture(doneTexture);
	doneButton.setPosition(Vector2f(503, 346));

	// Error Message
	Font font;
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	Text errorMessage;
	errorMessage.setFont(font);
	errorMessage.setFillColor(Color::Red);
	errorMessage.setCharacterSize(15);
	errorMessage.setPosition(Vector2f(171, 276));

	// Push Value Textbox
	TextBox indexTextbox(18, Color::White, false);
	indexTextbox.setPosition(Vector2f(375, 188));
	indexTextbox.setFont(font);
	indexTextbox.setLimit(true, 1);

	while (pushWindow.isOpen()) {
		Event aevent;
		Vector2i mousePos = Mouse::getPosition(pushWindow);

		while (pushWindow.pollEvent(aevent)) {
			switch (aevent.type) {
			case (Event::Closed):
				pushWindow.close();
				option = 0;
				break;
			case (Event::MouseButtonPressed):
				cout << mousePos.x << ", " << mousePos.y << endl;
				if (mousePos.x > 171 && mousePos.x < 171 + 257 && mousePos.y > 174 && mousePos.y < 174 + 52) {
					indexTextbox.setSelected(true);
				}
				else {
					indexTextbox.setSelected(false);
				}
				if (utils::isHover(doneButton, mousePos)) {

					if (!indexTextbox.isEmpty()) {
						int value = stoi(indexTextbox.getText());
						
						pushWindow.close();
						option = 0;

						// Start Pushing
						startPushing(value);

						clock.restart();
						stopSearching();
						stopDeleting();

						pushWindow.close();
						
					}
					else {
						errorMessage.setString("Index is Required!");
					}
				}
			case (Event::TextEntered):
				indexTextbox.typedOn(aevent);
			}

		}
		if (utils::isHover(doneButton, mousePos)) {
			doneTexture.loadFromFile("resources/buttons/DoneButton_selected.png");
			doneButton.setTexture(doneTexture);
		}
		else {
			doneTexture.loadFromFile("resources/buttons/DoneButton.png");
			doneButton.setTexture(doneTexture);
		}

		pushWindow.clear();
		pushWindow.draw(pushBg);
		pushWindow.draw(doneButton);
		pushWindow.draw(errorMessage);
		indexTextbox.drawTo(pushWindow);
		pushWindow.display();
	
	}

}

void Stack::drawPop(int& option) {

	deleteIndex = 0;

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


	if (arrSize == 0) {
		codeBlock.setSelectedLine(0);
		stopDeleting();
	}

	// Array related
	arrStates.clear();
	arrStates.push_back(arr);
	
	deleting = true;
	deleteStep = 0;

	option = 0;
}


void Stack::displayControlOptions(int& option, RenderWindow& window, Event& event) {
	// initialize
	if (option == 1) {
		drawInitialize(option);
	}
	// push
	else if (option == 2) {
		drawPush(option);

	}
	// pop
	else if (option == 3) {
		drawPop(option);
		stopSearching();
	}
	// Peak
	else if (option == 4) {
		stopDeleting();

		codeBlock.setIsOpen(true);
		codeBlock.codelines[0] = "if empty, return NOT_FOUND";
		codeBlock.codelines[1] = "return head.value";
		option = 0;
		for (int i = 2; i < codeBlock.codelines.size(); i++)
			codeBlock.codelines[i] = "";

		if (arrSize == 0) {
			codeBlock.setSelectedLine(0);
			stopSearching();
		}
		else {
			search_value = arr[0];
			found = true;
			searching = true;
			searchStep = 0;
			codeBlock.setSelectedLine(1);
		}
	}
	// Clear
	else if (option == 5) {
		stopDeleting();
		inserting = false;
		stopSearching();
		stopUpdating();
		arrStates.clear();
		arr.clear();
		arrSize = 0;
	}
}

Stack::~Stack() {}