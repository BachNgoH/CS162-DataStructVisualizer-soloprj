#pragma once
#include "BasePage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class DoublyLL : public BasePage
{

	void visualize(RenderWindow& window, Event& event);

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();
public:
	DoublyLL();
	~DoublyLL();
	void display(RenderWindow& window, Event& event, int& displayMode);

};