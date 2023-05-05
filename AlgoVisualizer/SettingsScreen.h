#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <string>
using namespace std;
using namespace sf;

class SettingScreen {
	Color bgColor;
	vector<vector<vector<int>>> colorPalletes;
	vector<string> palleteNames;
	int selectedPallete;

public:
	SettingScreen();
	~SettingScreen();
	void display(RenderWindow& window, Event& event, int &displayOption, vector<Color> &pallete, int &palleteCode);

};