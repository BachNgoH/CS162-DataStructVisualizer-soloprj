#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
using namespace sf;
using namespace std;

class HomeScreen {
	string bgPath;
	vector<string> cardPaths;
	vector<Vector2f> cardPositions;
	View homeView;
	int cardsNum;
	int viewOption;
	Clock clock;

	vector<Sprite> drawCards(RenderWindow &window, Event &event, int viewOption);
	vector<Sprite> getButtons(RenderWindow& window, Event& event, int viewOption);
	void drawBackground(RenderWindow& window);

	public:
		HomeScreen(RenderWindow &window);
		HomeScreen(string bgPath, vector<string> cardPaths, vector
			<Vector2f> cardPositions, RenderWindow &window);
		~HomeScreen();

		void display(RenderWindow &window, Event &event, int &displayMode);
		void calcHomeView(RenderWindow &window);

};

