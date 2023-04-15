#pragma once
#include "BasePage.h"
#include "SinglyLL.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Stack : public SinglyLL
{

	void drawPush(int &option);
	void drawPop(int &option);

	void startPushing(int value);
	void displayControlOptions(int& option, RenderWindow& window, Event& event) override;
public:
	Stack();
	~Stack();
	// void display(RenderWindow& window, Event& event, int& displayMode);

};