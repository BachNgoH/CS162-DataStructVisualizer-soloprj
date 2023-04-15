#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
#include <stack>
using namespace sf;
using namespace std;

class BasePage {
public:

	string bgPath;
	vector<int> arr;
	vector<vector<int>> arrStates;

	int option = 0;
	int arrSize = -1;
	bool isVisualizing = false;
	float visualizingSpeed = 1.0;
	Font font;
	Clock clock;
	bool includeSize = true;
	
	bool isPaused = false;
	int clickDelay = 0;

	BasePage();
	~BasePage();
	void display(RenderWindow& window, Event& event, int& displayMode);
	void displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect,
		int& option, int& initializeOpt, Text& errorMessage);
	void displayControlOptions(int& option, RenderWindow& window, Event& event);
	void drawPageLayout(RenderWindow& window, Event& event, int& displayMode);
	void drawPlayerControls(RenderWindow& window, Event& event);

	virtual void startSearching(int value);
	virtual void stopSearching();

	virtual void startDeleting(int index);
	virtual void stopDeleting();
	virtual void initVisualizing(int& option, int initializeOptions);
	virtual void drawInsert(int& option);
	virtual void drawUpdate(int& option);
	virtual void nextStep();
	virtual void previousStep();
	virtual void pauseAnimation();
};