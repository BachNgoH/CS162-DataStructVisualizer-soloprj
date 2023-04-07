#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
using namespace sf;
using namespace std;

class StaticArray
{
	string bgPath;
	vector<int> arr;
	int option = 0;
	int arrSize = -1;
	bool isVisualizing = false;
	float visualizingSpeed = 1.0;
	
	// search function
	Clock clock;
	int searchStep = 0;
	bool searching = false;
	int search_value;

	// delete function
	int deleteStep = 0;
	bool deleting = false;
	int deleteIndex;

	void visualize(RenderWindow& window, Event& event);

	public:
		StaticArray();
		~StaticArray();
		void display(RenderWindow& window, Event &event, int &displayMode);
		void displayCreateOpts(RenderWindow& window, Event& event, TextBox& sizeTextBox, RectangleShape& sizeRect, 
			int &option, int &initializeOpt, Text &errorMessage);
		void displayControlOptions(int& option, RenderWindow& window, Event& event);
		void search();
		void deleteAtIndex();
};

