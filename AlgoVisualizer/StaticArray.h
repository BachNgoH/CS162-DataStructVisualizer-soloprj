#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace sf;
using namespace std;

class StaticArray
{
	string bgPath;

	public:
		StaticArray();
		~StaticArray();
		void display(RenderWindow& window, Event &event, int &displayMode);
};

