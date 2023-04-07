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
using namespace sf;

int main() {

	int displayMode = 0;
	RenderWindow window(VideoMode(1440, 1024), "DSVisual", Style::Close | Style::Titlebar);
	HomeScreen home(window);
	
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
			staticArr.display(window, event, displayMode);
			break;
		case 2:
			dynamicArr.display(window, event, displayMode);
			break;
		case 3:
			singlyLL.display(window, event, displayMode);
			break;
		case 4:
			doublyLL.display(window, event, displayMode);
			break;
		case 5:
			circleLL.display(window, event, displayMode);
			break;
		case 6:
			queue.display(window, event, displayMode);
			break;
		case 7:
			stack.display(window, event, displayMode);
			break;
		default:
			break;
		}
		window.display();
	}

	return 0;
}