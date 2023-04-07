#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
using namespace sf;
using namespace std;

class BasePage {
	string bgPath;
	vector<int> arr;
	int option = 0;
	int arrSize = -1;
	bool isVisualizing = false;
	float visualizingSpeed = 1.0;

	public:
		BasePage();
		~BasePage();
		void display(RenderWindow& window, Event& event, int& displayMode);
		void displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect,
			int& option, int& initializeOpt, Text& errorMessage);
		void displayControlOptions(int& option, RenderWindow& window, Event& event);

		virtual void startSearching();
		virtual void stopSearching();

		virtual void startDeleting();
		virtual void stopDeleting();
};