#include "BasePage.h"
#include "utils.h"
#include <iostream>

enum InitializeOptions {
	EMPTY = 0,
	RANDOM = 1,
	USER_DEFINED = 2,
};

BasePage::BasePage() {
	font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
}

void BasePage::displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect,
	int& option, int& intializeOpt, Text& errorMessage) {
		vector<string> options = { "Empty", "Random", "User Input", "Size" };
	vector<Vector2f> positions = { {182, 67}, {182, 128}, {182, 189}, {182, 291} };
	vector<Vector2f> textPositions = { {270, 75}, {264, 136}, {240, 197}, {222, 299} };

	Font font;
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");



	Vector2i mousePos = Mouse::getPosition(window);

	for (size_t i = 0; i < options.size(); i++) {
		RectangleShape box;
		box.setSize(Vector2f(236, 41));
		box.setPosition(positions[i]);
		box.setFillColor(Color(217, 217, 217));

		Text text;
		text.setString(options[i]);
		text.setCharacterSize(20);
		text.setPosition(textPositions[i]);
		text.setFont(font);
		text.setFillColor(Color::Black);

		if (utils::isHover(box, mousePos)) {
			box.setFillColor(Color::Black);
			text.setFillColor(Color::White);
		}

		if (intializeOpt == i || i == options.size() - 1)
			box.setFillColor(Color(255, 153, 0));

		if (event.type == Event::MouseButtonPressed) {
			if (utils::isHover(box, mousePos) && i != options.size() - 1) {
				intializeOpt = i;
			}
		}

		window.draw(box);
		window.draw(text);
	}

	Texture doneTexture;
	doneTexture.loadFromFile("resources/buttons/DoneButton.png");

	Sprite doneButton;
	doneButton.setTexture(doneTexture);
	doneButton.setPosition(Vector2f(503, 346));

	if (utils::isHover(doneButton, mousePos)) {
		doneTexture.loadFromFile("resources/buttons/DoneButton_selected.png");
		doneButton.setTexture(doneTexture);
	}
	
	if (event.type == Event::MouseButtonPressed) {


		if (utils::isHover(doneButton, mousePos)) {
			if (sizeTextBox.isEmpty()) {
				errorMessage.setString("array size is required!");
			}
			else if (stoi(sizeTextBox.getText()) > 10) {
				errorMessage.setString("array size must be <= 10");
			}
			else {
				arrSize = stoi(sizeTextBox.getText());
				isVisualizing = true;
				arr.resize(arrSize);
				stopSearching();

				cout << "INIT OPT: " << intializeOpt << endl;
				switch (intializeOpt) {
				case InitializeOptions::EMPTY:
					for (int i = 0; i < arrSize; i++) {
						arr[i] = 1000;
					}
					break;
				case InitializeOptions::RANDOM:
					for (int i = 0; i < arrSize; i++) {
						arr[i] = rand() % 100;
					}
					break;
				default:
					break;
				}
				window.close();
				option = 0;
			}
		}
	}



	window.draw(sizeRect);
	sizeTextBox.drawTo(window);
	window.draw(doneButton);
	window.draw(errorMessage);
	//cout << sizeTextBox.getText() << endl;
}

void BasePage::displayControlOptions(int& option, RenderWindow& window, Event& event) {

	// initialize
	if (option == 1) {
		RenderWindow initializeWindow(VideoMode(600, 400), "Initialize", Style::Close | Style::Titlebar);

		Font font;
		font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");

		// Error Message
		Text errorMessage;
		errorMessage.setFont(font);
		errorMessage.setFillColor(Color::Red);
		errorMessage.setPosition(175, 350);
		errorMessage.setCharacterSize(18);

		// Define Size Text Box
		TextBox sizeTextBox(20, Color::Black, false);
		sizeTextBox.setFont(font);
		sizeTextBox.setPosition(Vector2f(376, 297));
		sizeTextBox.setLimit(true, 1);
		//sizeTextBox.setString(std::to_string(arrSize));

		RectangleShape sizeRect;
		sizeRect.setFillColor(Color(217, 217, 217));
		sizeRect.setSize(Vector2f(43, 24));
		sizeRect.setPosition(Vector2f(367, 299));

		int initializeOpt;
		initializeOpt = InitializeOptions::EMPTY;

		while (initializeWindow.isOpen()) {
			Event aevent;
			Vector2i mousePos = Mouse::getPosition(initializeWindow);

			while (initializeWindow.pollEvent(aevent)) {
				switch (aevent.type) {
				case (Event::Closed):
					initializeWindow.close();
					option = 0;
					break;
				case (Event::MouseButtonPressed):
					if (utils::isHover(sizeRect, mousePos)) {
						//cout << "HERE 1" << endl;
						sizeTextBox.setSelected(true);
					}
					else {
						sizeTextBox.setSelected(false);
					}
					break;
				case (Event::TextEntered):
					sizeTextBox.typedOn(aevent);
					break;
				default:
					continue;
				}
			}
			initializeWindow.clear(Color(232, 232, 232));
			displayCreateOpts(initializeWindow, aevent, sizeTextBox, sizeRect, option,
				initializeOpt, errorMessage);
			initializeWindow.display();
		}
	}
	// add & update
	else if (option == 2 || option == 4) {
		string windowTitle;
		if (option == 2)
			windowTitle = "Add To Array";
		else
			windowTitle = "Update Array";

		RenderWindow addWindow(VideoMode(600, 400), windowTitle, Style::Close | Style::Titlebar);
		Font font;
		font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");

		TextBox valueTextBox(18, Color::White, false);
		valueTextBox.setFont(font);
		valueTextBox.setPosition(Vector2f(376, 106));
		valueTextBox.setLimit(true, 1);
		//sizeTextBox.setString(std::to_string(arrSize));

		Texture vboxTexture;
		vboxTexture.loadFromFile("resources/blocks/ValueBox.png");
		Sprite valueBox;
		valueBox.setTexture(vboxTexture);
		valueBox.setPosition(Vector2f(171, 92));

		TextBox indexTextBox(18, Color::White, false);
		indexTextBox.setFont(font);
		indexTextBox.setPosition(Vector2f(376, 215));
		indexTextBox.setLimit(true, 1);

		Texture iboxTexture;
		iboxTexture.loadFromFile("resources/blocks/IndexBox.png");
		Sprite indexBox;
		indexBox.setTexture(iboxTexture);
		indexBox.setPosition(Vector2f(171, 200));

		Texture doneTexture;
		doneTexture.loadFromFile("resources/buttons/DoneButton.png");

		Sprite doneButton;
		doneButton.setTexture(doneTexture);
		doneButton.setPosition(Vector2f(503, 346));

		Text errorMessage;
		errorMessage.setFont(font);
		errorMessage.setFillColor(Color::Red);
		errorMessage.setCharacterSize(15);
		errorMessage.setPosition(Vector2f(171, 276));

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
					if (utils::isHover(valueBox, mousePos)) {
						valueTextBox.setSelected(true);
						indexTextBox.setSelected(false);
					}
					else if (utils::isHover(indexBox, mousePos)) {
						valueTextBox.setSelected(false);
						indexTextBox.setSelected(true);
					}
					else {
						valueTextBox.setSelected(false);
						indexTextBox.setSelected(false);
					}

					if (utils::isHover(doneButton, mousePos)) {

						if (!valueTextBox.isEmpty() && !indexTextBox.isEmpty()) {
							int index = stoi(indexTextBox.getText());
							int value = stoi(valueTextBox.getText());

							if (index >= arrSize || index < 0) {
								//cout << errorMessage.getString().toAnsiString() << endl;
								errorMessage.setString("Invalid index");
							}
							else {

								arr[index] = value;
								addWindow.close();
								option = 0;
							}
						}
						else {
							errorMessage.setString("Value and Index are Required!");
						}
					}
					break;
				default:
					break;
				}
			}

			addWindow.clear(Color(232, 232, 232));

			if (utils::isHover(doneButton, mousePos)) {
				doneTexture.loadFromFile("resources/buttons/DoneButton_selected.png");
				doneButton.setTexture(doneTexture);
			}
			else {
				doneTexture.loadFromFile("resources/buttons/DoneButton.png");
				doneButton.setTexture(doneTexture);
			}

			addWindow.draw(doneButton);
			addWindow.draw(valueBox);
			addWindow.draw(indexBox);
			valueTextBox.drawTo(addWindow);
			indexTextBox.drawTo(addWindow);
			addWindow.draw(errorMessage);

			addWindow.display();
		}
	}
	// 
	else if (option == 5) {

		RenderWindow searchWindow(VideoMode(600, 400), "Search", Style::Close | Style::Titlebar);
		Texture bgTexture;
		bgTexture.loadFromFile("resources/backgrounds/Search-bg.png");
		Sprite searchBg;
		searchBg.setTexture(bgTexture);

		// Done button
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

		// Search Value Textbox
		TextBox valueTextbox(18, Color::White, false);
		valueTextbox.setPosition(Vector2f(375, 188));
		valueTextbox.setFont(font);
		valueTextbox.setLimit(true, 1);

		while (searchWindow.isOpen()) {
			Event aevent;
			Vector2i mousePos = Mouse::getPosition(searchWindow);

			while (searchWindow.pollEvent(aevent)) {
				switch (aevent.type) {
				case (Event::Closed):
					searchWindow.close();
					option = 0;
					break;
				case (Event::MouseButtonPressed):
					cout << mousePos.x << ", " << mousePos.y << endl;
					if (mousePos.x > 171 && mousePos.x < 171 + 257 && mousePos.y > 174 && mousePos.y < 174 + 52) {
						cout << "HERE" << endl;
						valueTextbox.setSelected(true);
					}
					else {
						valueTextbox.setSelected(false);
					}
					if (utils::isHover(doneButton, mousePos)) {

						if (!valueTextbox.isEmpty()) {
							int value = stoi(valueTextbox.getText());
							// Start Search
							startSearching(value);
							clock.restart();
							stopDeleting();
							searchWindow.close();
						}
						else {
							errorMessage.setString("Value and Index are Required!");
						}
					}
				case (Event::TextEntered):
					valueTextbox.typedOn(aevent);
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

			searchWindow.clear();
			searchWindow.draw(searchBg);
			searchWindow.draw(doneButton);
			searchWindow.draw(errorMessage);
			valueTextbox.drawTo(searchWindow);
			searchWindow.display();
		}
	}
	else if (option == 3) {
		RenderWindow deleteWindow(VideoMode(600, 400), "Delete", Style::Titlebar | Style::Close);
		Texture bgTexture;
		bgTexture.loadFromFile("resources/backgrounds/Delete-bg.png");
		Sprite deleteBg;
		deleteBg.setTexture(bgTexture);

		// Done button
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

		// Search Value Textbox
		TextBox indexTextbox(18, Color::White, false);
		indexTextbox.setPosition(Vector2f(375, 188));
		indexTextbox.setFont(font);
		indexTextbox.setLimit(true, 1);

		while (deleteWindow.isOpen()) {
			Event aevent;
			Vector2i mousePos = Mouse::getPosition(deleteWindow);

			while (deleteWindow.pollEvent(aevent)) {
				switch (aevent.type) {
				case (Event::Closed):
					deleteWindow.close();
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
							int index = stoi(indexTextbox.getText());
							deleteWindow.close();
							option = 0;

							// Start Delete
							startDeleting(index);
							clock.restart();
							stopSearching();
							deleteWindow.close();

						}
						else {
							errorMessage.setString("Value and Index are Required!");
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

			deleteWindow.clear();
			deleteWindow.draw(deleteBg);
			deleteWindow.draw(doneButton);
			deleteWindow.draw(errorMessage);
			indexTextbox.drawTo(deleteWindow);
			deleteWindow.display();
		}
	}
}

void BasePage::startSearching(int value) {}
void BasePage::stopSearching() {}
void BasePage::startDeleting(int index) {}
void BasePage::stopDeleting() {}

void BasePage::drawPageLayout(RenderWindow& window, Event& event, int &displayMode) {
	Texture bgTexture;
	bgTexture.loadFromFile(bgPath);
	Sprite bg(bgTexture);

	Text back;
	back.setFont(font);
	back.setString("<");
	back.setCharacterSize(20);
	back.setFillColor(Color::White);
	back.setPosition(19.f, 13.f);

	Font controlFont;
	controlFont.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
	vector<string> controlOptions = { "Initialize", "Add", "Delete", "Update", "Search" };
	vector<Text> controls;
	vector<RectangleShape> controlRects;

	controls.resize(5);
	controlRects.resize(5);
	
	for (size_t i = 0; i < controls.size(); i++) {

		controls[i].setFont(controlFont);
		controls[i].setString(controlOptions[i]);
		controls[i].setPosition(50, 742 + i * 36);
		controls[i].setCharacterSize(20);
		controls[i].setFillColor(Color::White);

		controlRects[i].setFillColor(Color(255, 153, 0));
		controlRects[i].setSize(Vector2f(334.f, 39.f));
		controlRects[i].setPosition(23, 728 + i * 39);

		if (!isVisualizing && i != 0) {
			controlRects[i].setFillColor(Color(217, 217, 217));
		}
	}

	Vector2i mousePos;

	if (event.type == Event::MouseMoved)
		mousePos = Mouse::getPosition(window);
	if (utils::isHover(back, mousePos)) {
		Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Hand))
			window.setMouseCursor(cursor);
		back.setFillColor(Color(255, 153, 0));

	}
	else {
		Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
			window.setMouseCursor(cursor);
	}

	if (event.type == Event::MouseButtonPressed) {
		mousePos = Mouse::getPosition(window);
		if (utils::isHover(back, mousePos))
			displayMode = 0;

		for (size_t i = 0; i < controls.size(); i++) {
			if (utils::isHover(controlRects[i], mousePos)) {
				if (i == 0)
					option = 1;
				else if (isVisualizing)
					option = i + 1;
			}
		}

		//cout << option << endl;
	}
	window.draw(bg);

	for (size_t i = 0; i < controls.size(); i++) {
		if (utils::isHover(controlRects[i], mousePos) && (isVisualizing || i == 0)) {
			controlRects[i].setFillColor(Color::Black);
		}

		window.draw(controlRects[i]);
		window.draw(controls[i]);
	}

	displayControlOptions(option, window, event);
	window.draw(back);
}

BasePage::~BasePage() {}