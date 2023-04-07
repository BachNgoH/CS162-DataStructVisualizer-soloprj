#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
#include "BasePage.h"
using namespace sf;
using namespace std;

class StaticArray: public BasePage
{

	// search function
	int searchStep = 0;
	bool searching = false;
	int search_value;

	// delete function
	int deleteStep = 0;
	bool deleting = false;
	int deleteIndex;

	void visualize(RenderWindow& window, Event& event);
	
	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();

	public:
		StaticArray();
		~StaticArray();
		void display(RenderWindow& window, Event& event, int& displayMode);
		void search();
		void deleteAtIndex();


};

