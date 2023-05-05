#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "HomeScreen.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "SinglyLL.h"
#include "DoublyLL.h"
#include "CircularLL.h"
#include "Stack.h"
#include "Queue.h"
#include "SettingsScreen.h"
using namespace sf;

int main() {

	int displayMode = 0;
	RenderWindow window(VideoMode(1440, 1024), "DSVisual", Style::Close | Style::Titlebar);
	HomeScreen home(window);
	SettingScreen setting;
	srand(time(0));

	int palleteCode = 0;
	vector<Color> pallate = { Color(137, 13, 196), Color(255,153,0), Color(56,174,204), Color(22, 185, 132) };

	// Data Structures
	StaticArray staticArr; 
	DynamicArray dynamicArr; 
	SinglyLL singlyLL; 
	DoublyLL doublyLL; 
	CircularLL circleLL; 
	Stack stack;
	Queue queue; 

	//window.setFramerateLimit(60);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		switch (displayMode) {
		case 0:
			home.display(window, event, displayMode);
			break;
		case 1:
			staticArr.pallete = pallate;
			staticArr.palleteCode = palleteCode;
			staticArr.display(window, event, displayMode);
			break;
		case 2:
			dynamicArr.palleteCode = palleteCode;
			dynamicArr.pallete = pallate;
			dynamicArr.display(window, event, displayMode);
			break;
		case 3:
			singlyLL.palleteCode = palleteCode;
			singlyLL.pallete = pallate;
			singlyLL.display(window, event, displayMode);
			break;
		case 4:
			doublyLL.palleteCode = palleteCode;
			doublyLL.pallete = pallate;
			doublyLL.display(window, event, displayMode);
			break;
		case 5:
			circleLL.palleteCode = palleteCode;
			circleLL.pallete = pallate;
			circleLL.display(window, event, displayMode);
			break;
		case 6:
			queue.palleteCode = palleteCode;
			queue.pallete = pallate;
			queue.display(window, event, displayMode);
			break;
		case 7:
			stack.palleteCode = palleteCode;
			stack.pallete = pallate;
			stack.display(window, event, displayMode);
			break;
		case 8:
			setting.display(window, event, displayMode, pallate, palleteCode);
			break;
		default:
			break;
		}
		window.display();
	}

	return 0;
}