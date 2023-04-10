#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
using namespace sf;
using namespace std;

class BasePage {
public:

	string bgPath;
	vector<int> arr;
	int option = 0;
	int arrSize = -1;
	bool isVisualizing = false;
	float visualizingSpeed = 1.0;
	Font font;
	Clock clock;
	bool includeSize = true;

	BasePage();
	~BasePage();
	void display(RenderWindow& window, Event& event, int& displayMode);
	void displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect,
		int& option, int& initializeOpt, Text& errorMessage);
	void displayControlOptions(int& option, RenderWindow& window, Event& event);
	void drawPageLayout(RenderWindow& window, Event& event, int& displayMode);

	virtual void startSearching(int value);
	virtual void stopSearching();

	virtual void startDeleting(int index);
	virtual void stopDeleting();
	virtual void initVisualizing(int& option, int initializeOptions);
	virtual void drawInsert(int& option);
	virtual void drawUpdate(int& option);

};