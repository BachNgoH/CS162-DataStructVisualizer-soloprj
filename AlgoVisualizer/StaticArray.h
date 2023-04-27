#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TextBox.h"
#include "BasePage.h"
#include "InsertOptions.h"
#include "CodeCell.h"
using namespace sf;
using namespace std;

class StaticArray: public BasePage
{

	// search function
	int searchStep = 0;
	bool searching = false;
	int search_value;

	// delete function
	int deleteStep = 0;
	bool deleting = false;
	int deleteIndex;

	// insert function
	bool inserting = false;
	int insertIndex = 0;
	int insertValue = 0;
	int insertStep = 0;
	int totalInsertStep = 0;
	float insertStepTime = 1000.f;
	CodeCell codeBlock;

	void visualize(RenderWindow& window, Event& event);

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();
	
	void startInserting(int index, int value);
	void setCodeBlockInsert();
	void initVisualizing(int &option);
	void drawCodeCells(RenderWindow& window, Event& event);

	void previousStep();
	void nextStep();

	public:
		StaticArray();
		~StaticArray();
		void display(RenderWindow& window, Event& event, int& displayMode);
		void search();
		void deleteAtIndex();
		void insertToArray();

};

