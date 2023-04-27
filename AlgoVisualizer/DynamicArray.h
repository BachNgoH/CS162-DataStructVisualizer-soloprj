#pragma once

#include "BasePage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "CodeCell.h"
#include "InsertOptions.h"

class DynamicArray : public BasePage
{
public:
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

	// Update Attributes
	bool updating = false;
	int updateIndex;

	void startSearching(int value);
	void stopSearching();
	void startDeleting(int index);
	void stopDeleting();
	void startInserting(int index, int value);
	void startUpdating(int value, int index);
	void stopUpdating();

	void previousStep();
	void nextStep();

	void insertToArray();
	void initVisualizing(int& option, int initializeOptions) override;
	void search();
	void deleteAtIndex();
	void drawCodeCells(RenderWindow& window, Event& event);


	void setCodeBlockDelete();
	void setCodeBlockInsert();
	void setCodeBlockSearch();

	virtual void visualize(RenderWindow& window, Event& event);
	virtual void displayControlOptions(int& option, RenderWindow& window, Event& event);

	DynamicArray();
	~DynamicArray();
	void display(RenderWindow& window, Event& event, int& displayMode);

};