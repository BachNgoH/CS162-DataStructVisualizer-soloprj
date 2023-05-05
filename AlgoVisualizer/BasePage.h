#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
#include <stack>
#include "InsertOptions.h"
using namespace sf;
using namespace std;

class BasePage {
public:
	int maxArrSize = 10;

	string bgPath;
	vector<int> arr;
	vector<vector<int>> arrStates;
	vector<string> controlOptions;

	int option = 0;
	int arrSize = -1;
	bool isVisualizing = false;
	float visualizingSpeed = 1.0;
	Font font;
	Clock clock;
	bool includeSize = true;
	
	bool isPaused = false;
	int clickDelay = 0;
	vector<Color> pallete;
	int palleteCode;

	BasePage();
	~BasePage();
	void display(RenderWindow& window, Event& event, int& displayMode);
	void displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect,
		int& option, int& initializeOpt, Text& errorMessage);
	virtual void displayControlOptions(int& option, RenderWindow& window, Event& event);
	void drawPageLayout(RenderWindow& window, Event& event, int& displayMode);
	void drawPlayerControls(RenderWindow& window, Event& event);


	virtual void startSearching(int value);
	virtual void stopSearching();

	virtual void startDeleting(int index);
	virtual void stopDeleting();
	virtual void initVisualizing(int& option, int initializeOptions);
	
	virtual void startUpdating(int value, int index);
	virtual void stopUpdating();

	virtual void startInserting(int value, int index);

	virtual void drawInsert(int& option);
	virtual void drawUpdate(int& option);
	virtual void drawInitialize(int& option);
	virtual void drawDelete(int& option);
	virtual void drawSearch(int& option);
	
	virtual void nextStep();
	virtual void previousStep();
	virtual void pauseAnimation();
};