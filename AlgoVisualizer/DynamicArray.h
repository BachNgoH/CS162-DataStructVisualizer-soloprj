#pragma once
#include "BasePage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class DynamicArray : public BasePage
{

	void visualize(RenderWindow& window, Event& event);

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();
public:
	DynamicArray();
	~DynamicArray();
	void display(RenderWindow& window, Event& event, int& displayMode);

};