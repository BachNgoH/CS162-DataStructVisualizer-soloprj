#include "SettingsScreen.h"
#include "utils.h"
SettingScreen::SettingScreen() {
	bgColor = Color(232,232,232);
	colorPalletes = {
		{{137, 13, 196}, {255, 153, 0}, {56, 174, 204}, {22, 185, 132}},
		{{249, 123, 34}, {194, 175, 128}, {156, 167, 119}, {124, 144, 112}},
		{{139, 24, 116}, {183, 19, 117}, {252, 79, 0}, {247, 149, 64}},
	};
	palleteNames = { "Standard", "Vintage", "Warm" };
	selectedPallete = 0;
}

void SettingScreen::display(RenderWindow& window, Event& event, int &displayOption, vector<Color> &pallete, int &palleteCode) {
	RectangleShape bg;
	bg.setFillColor(bgColor);
	bg.setSize(Vector2f(window.getSize().x, window.getSize().y));

	window.draw(bg);

	Font font; font.loadFromFile("resources/fonts/PressStart2P-Regular.ttf");
	Text back;
	back.setFont(font);
	back.setString("<");
	back.setCharacterSize(20);
	back.setFillColor(Color::White);
	back.setPosition(19.f, 13.f);

	if (utils::isHover(back, Mouse::getPosition(window)))
		back.setFillColor(Color(255, 153, 0));

	if (event.type == Event::MouseButtonPressed && utils::isHover(back, Mouse::getPosition(window)))
		displayOption = 0;

	RectangleShape navBar;
	navBar.setFillColor(Color::Black);
	navBar.setSize(Vector2f(window.getSize().x, 47));

	window.draw(navBar);
	window.draw(back);

	Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setString("Setting");
	text.setPosition(560, 79);
	text.setFillColor(Color::Black);
	window.draw(text);

	for (size_t i = 0; i < colorPalletes.size(); i++)
	{
		RectangleShape palleteContainer;
		palleteContainer.setFillColor(Color(217, 217, 217));
		palleteContainer.setSize(Vector2f(449, 71));
		palleteContainer.setPosition(Vector2f(495, 238 + 141 * i));
		if (i == selectedPallete) {
			palleteContainer.setOutlineColor(Color(22, 185, 132));
			palleteContainer.setOutlineThickness(4);
		}
		Vector2i mousePos = Mouse::getPosition(window);
		if (utils::isHover(palleteContainer, mousePos)) {
			palleteContainer.setOutlineColor(Color(56, 174, 204));
			palleteContainer.setOutlineThickness(4);
		}

		Font textFont; 
		textFont.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
		Text text; text.setFillColor(Color::Black);
		text.setString(palleteNames[i]);
		text.setFont(textFont);
		text.setPosition(495, 200 + 141 * i);

		window.draw(palleteContainer);
		window.draw(text);

		if (event.type == Event::MouseButtonPressed && utils::isHover(palleteContainer, mousePos))
			selectedPallete = i;

		for (size_t j = 0; j < colorPalletes[i].size(); j++) {
			RectangleShape colorBox;
			colorBox.setFillColor(Color(colorPalletes[i][j][0], colorPalletes[i][j][1], colorPalletes[i][j][2]));
			colorBox.setSize(Vector2f(40, 40));
			colorBox.setPosition( 527 + 116 * j ,254 + i*141);
			window.draw(colorBox);
		}
	}

	vector<vector<int>> tempPallete = colorPalletes[selectedPallete];
	vector<Color> tempColor = { Color(tempPallete[0][0], tempPallete[0][1], tempPallete[0][2]),
		Color(tempPallete[1][0], tempPallete[1][1], tempPallete[1][2]),
		Color(tempPallete[2][0], tempPallete[2][1], tempPallete[2][2]),
		Color(tempPallete[3][0], tempPallete[3][1], tempPallete[3][2])
	};
	pallete = tempColor;
	palleteCode = selectedPallete;
}

SettingScreen::~SettingScreen() {};