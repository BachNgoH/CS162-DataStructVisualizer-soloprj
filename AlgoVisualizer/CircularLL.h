#pragma once
#include "BasePage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class CircularLL : public BasePage
{

	void visualize(RenderWindow& window, Event& event);

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();
public:
	CircularLL();
	~CircularLL();
	void display(RenderWindow& window, Event& event, int& displayMode);

};