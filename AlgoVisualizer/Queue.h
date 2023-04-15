#pragma once
#include "BasePage.h"
#include "SinglyLL.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Queue : public SinglyLL
{

	void drawEnqueue(int& option);
	void drawDequeue(int& option);

	void startEnqueue(int value);
	void displayControlOptions(int& option, RenderWindow& window, Event& event) override;

public:
	Queue();
	~Queue();

};