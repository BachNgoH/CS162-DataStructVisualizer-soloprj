#pragma once
#include "SinglyLL.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class CircularLL : public SinglyLL
{

	void visualize(RenderWindow& window, Event& event);

public:
	CircularLL();
	~CircularLL();

};