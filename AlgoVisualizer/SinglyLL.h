#pragma once
#include "BasePage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "CodeCell.h"

enum InsertOption {
	HEAD = 0,
	TAIL = 1,
	INDEX = 2,
};

class SinglyLL : public BasePage
{
	// Search Attributes
	bool searching = false;
	int searchStep = 0;
	int search_value;
	float searchStepTime = 1000.f;
	bool found = false;

	// Insert Attributes
	bool inserting = false;
	int insertIndex = 0;
	int insertValue = 0;
	int insertStep = 0;
	int totalInsertStep = 0;
	float insertStepTime = 1000.f;
	int mode = InsertOption::HEAD;

	// Delete Attributes
	bool deleting = false;
	int deleteIndex;
	int deleteStep = 0;
	float deleteStepTime = 500.f;
	int totalDeleteStep = 0;
	CodeCell codeBlock;

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();	
	void startInserting();

	void initVisualizing(int &option, int initializeOptions) override;
	void visualize(RenderWindow& window, Event& event);
	void drawInsert(int& option);
	void search();
	void deleteAtIndex();
	void drawCodeCells(RenderWindow &window, Event &event);

public:
	SinglyLL();
	~SinglyLL();
	void display(RenderWindow& window, Event& event, int& displayMode);

};