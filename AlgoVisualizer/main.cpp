#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "HomeScreen.h"
#include "StaticArray.h"
using namespace sf;

int main() {

	int displayMode = 0;
	RenderWindow window(VideoMode(1440, 1024), "DSVisual", Style::Close | Style::Titlebar);
	HomeScreen home(window);
	StaticArray staticArr;
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
		default:
			break;
		}
		window.display();
	}

	return 0;
}