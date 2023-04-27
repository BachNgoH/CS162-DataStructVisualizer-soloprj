#include "CircularLL.h"
#include <iostream>
#include "utils.h"
#include "TextBox.h"
#include <string>
#include "Arrow.h"

CircularLL::CircularLL() {
	bgPath = "resources/CircularLinkedList-Background.png";
	font.loadFromFile("resources/fonts/SourceCodePro-Regular.ttf");
}

void CircularLL::visualize(RenderWindow& window, Event& event) {

	if (isVisualizing) {
		vector<Sprite> allLLBlocks;
		allLLBlocks.resize(arr.size());
		// Draw Linked List Blocks
		for (int i = 0; i < arr.size(); i++) {

			Texture textureLL;
			textureLL.loadFromFile("resources/blocks/LinkedList.png");
			allLLBlocks[i].setTexture(textureLL);
			allLLBlocks[i].setPosition(Vector2f(127 + 160 * i, 250));

			Text value;
			value.setCharacterSize(18);
			value.setFont(font);
			value.setPosition(159 + 160 * i, 268);
			value.setString(to_string(arr[i]));
			value.setFillColor(Color::Black);

			// Insert Logic;
			if (inserting) {
				switch (mode) {
				case InsertOption::HEAD:
					if (insertStep == 0) {
						allLLBlocks[i].move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
						value.move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
					}
					else if (insertStep <= totalInsertStep) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				case InsertOption::INDEX:
					if (((insertStep < insertIndex && insertStep == i) ||
						(insertStep >= insertIndex && i == insertIndex - 1)) && \
						insertStep <= totalInsertStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep >= insertIndex && i == insertIndex && insertStep <= totalInsertStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (insertStep == insertIndex + 1 && i >= insertIndex) {
						allLLBlocks[i].move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
						value.move(160.f * min(clock.getElapsedTime().asMilliseconds() / insertStepTime, 1.f), 0);
					}
					else if (insertStep > insertIndex + 1 && insertStep <= totalInsertStep && i >= insertIndex) {
						allLLBlocks[i].move(160.f, 0);
						value.move(160.f, 0);
					}
					break;
				default:
					break;
				}

			}

			// Search Logic
			if (searching) {
				if (i <= searchStep) {
					textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
					allLLBlocks[i].setTexture(textureLL);
				}
				if (arr[i] == search_value && searchStep == i) {
					textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
					allLLBlocks[i].setTexture(textureLL);
				}
			}

			// Update Logic
			if (updating) {
				if (i == updateStep) {
					textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
					allLLBlocks[i].setTexture(textureLL);
				}
				if (i == updateIndex && updateStep == i) {
					textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
					allLLBlocks[i].setTexture(textureLL);
				}
			}

			// Delete Logic
			if (deleting) {
				if (mode == InsertOption::INDEX || mode == InsertOption::TAIL) {
					if (i == deleteStep && deleteStep < deleteIndex && deleteStep <= totalDeleteStep) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					if (deleteStep >= deleteIndex && deleteStep <= totalDeleteStep) {
						if (deleteStep >= deleteIndex + 2) {
							if (i == deleteIndex)
								continue;
							else if (i > deleteIndex && deleteStep <= totalDeleteStep) {
								allLLBlocks[i].move(-160 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
								value.move(-160 * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
							}
							else if (i > deleteIndex) {
								allLLBlocks[i].move(-160, 0);
								value.move(-160, 0);
							}

						}
						if (i == deleteIndex) {
							textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
							allLLBlocks[i].setTexture(textureLL);

							if (mode == InsertOption::INDEX) {
								if (deleteStep == deleteIndex + 1) {
									allLLBlocks[i].move(0, 100.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
									value.move(0, 100.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f));
								}
								else if (deleteStep > deleteIndex + 1) {
									allLLBlocks[i].move(0, 100.f);
									value.move(0, 100.f);
								}
							}
						}
						if ((i == deleteIndex - 1 || i == deleteIndex + 1) && deleteStep <= totalDeleteStep) {
							textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
							allLLBlocks[i].setTexture(textureLL);
						}
					}
				}
				else if (mode == InsertOption::HEAD) {
					if (i == deleteStep && deleteStep <= 1) {
						textureLL.loadFromFile("resources/blocks/LinkedList-search.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					else if (deleteStep == 1 && i == 0) {
						textureLL.loadFromFile("resources/blocks/LinkedList-found.png");
						allLLBlocks[i].setTexture(textureLL);
					}
					else if (deleteStep == 2 && i > 0) {
						allLLBlocks[i].move(-160.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
						value.move(-160.f * min(clock.getElapsedTime().asMilliseconds() / deleteStepTime, 1.f), 0);
					}
					else if (deleteStep == 2 && i == 0)
						continue;
				}
			}

			window.draw(allLLBlocks[i]);
			window.draw(value);
		}
		// Draw Arrows
		for (int i = 0; i < arrSize - 1; i++) {
			if (inserting && mode == InsertOption::INDEX && insertStep >= totalInsertStep - 2 &&
				insertStep <= totalInsertStep && i == insertIndex - 1)
				continue;
			Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[i])[1];
			Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[i + 1])[0];

			Arrow arrow(startPosition, endPosition, 5, Color::Black);
			int timeStep = clock.getElapsedTime().asMilliseconds();

			if (deleting) {
				arrow.setAnimatingTime(deleteStepTime);

				if (mode == InsertOption::INDEX || mode == InsertOption::TAIL) {
					if (deleteStep >= deleteIndex + 1 && deleteStep <= totalDeleteStep) {
						if (deleteStep >= deleteIndex + 2 && i == deleteIndex)
							continue;

						if (i == deleteIndex - 1 && i + 2 < arrSize) {
							arrow.setEndPosition(utils::get4sizesCoords(allLLBlocks[i + 2])[0]);
							arrow.drawToV2(window, timeStep, deleteStep == deleteIndex + 1);
							continue;
						}

						if (mode == InsertOption::TAIL && deleteStep >= deleteIndex + 1 && i == deleteIndex - 1) {
							// arrow.setAnimatingTime(5000.f);
							arrow.setEndPosition(utils::get4sizesCoords(allLLBlocks[0])[0]);
							arrow.drawReverseArrow(window, timeStep, deleteStep == deleteIndex + 1);
							
							continue;
						}
					}
					arrow.drawToV2(window, timeStep, (i == deleteStep && i < deleteIndex));
				}
				else if (mode == InsertOption::HEAD) {
					if (deleteStep > 1 && i == 0 && deleteStep <= totalDeleteStep)
						continue;
					arrow.drawToV2(window, timeStep, (i == deleteStep && deleteStep == 0));

				}
			}
			else if (inserting) {
				if (mode == InsertOption::HEAD)
					arrow.drawToV2(window, timeStep, (insertStep == i && i < insertIndex));
				else if (mode == InsertOption::INDEX)
					arrow.drawToV2(window, timeStep, (insertStep == i && i < insertIndex - 1));
				else
					arrow.drawToV2(window, timeStep, false);
			}
			else if (searching) {
				arrow.drawTo(window, timeStep, !inserting && (searching && searchStep == i && !found));
			}
			else {
				arrow.drawToV2(window, timeStep, false);
			}
		}

		// Draw reverse arrow
		if (arr.size() > 0) {
			Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[arr.size() - 1])[1];
			Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[0])[0];
			int timeStep = clock.getElapsedTime().asMilliseconds();
			Arrow reverseArrow(startPosition, endPosition, 5, Color::Black);

			if (deleting) {

				if (deleting && mode == InsertOption::HEAD && deleteStep == 2 && arr.size() > 1)
					endPosition = utils::get4sizesCoords(allLLBlocks[1])[0];

				if (mode != InsertOption::TAIL ||
					(deleteStep != deleteIndex + 1 && deleteStep != deleteIndex + 2))
					reverseArrow.drawReverseArrow(window, timeStep, deleting && mode == InsertOption::HEAD && deleteStep == 2);
			}
			else if (inserting) {
				if (mode == InsertOption::HEAD && (insertStep > 2 || insertStep <= 1)) {
					reverseArrow.drawReverseArrow(window, timeStep, false);
				}

			}
			else {
				reverseArrow.drawReverseArrow(window, timeStep, false);
			}
		}
		if (inserting) {
			switch (mode) {
			case InsertOption::HEAD:
				if (insertStep >= 1 && insertStep <= totalInsertStep) {
					Texture textureLL;
					textureLL.loadFromFile("resources/blocks/LinkedList.png");
					Sprite llBlock;
					llBlock.setTexture(textureLL);
					llBlock.setPosition(Vector2f(127 + 160 * insertIndex, 250));

					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * insertIndex, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					if (insertStep == 2 && arr.size() > 0) {
						int timeStep = clock.getElapsedTime().asMilliseconds();
						Vector2f startPosition = utils::get4sizesCoords(llBlock)[1];
						Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[0])[0];
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, true);

						Vector2f startPosition1 = utils::get4sizesCoords(allLLBlocks[arr.size() - 1])[1];
						Vector2f endPosition1 = utils::get4sizesCoords(llBlock)[0];
						Arrow reverseArrow(startPosition1, endPosition1, 5, Color::Black);
						reverseArrow.drawReverseArrow(window, timeStep, true);
					}
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::TAIL:
				if (insertStep >= 0 && insertStep <= totalInsertStep) {
					Texture textureLL;
					textureLL.loadFromFile("resources/blocks/LinkedList.png");
					Sprite llBlock;
					llBlock.setTexture(textureLL);
					llBlock.setPosition(Vector2f(127 + 160 * arrSize, 250));

					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * arrSize, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					if (insertStep == 1 && arrSize > 0) {
						int timeStep = clock.getElapsedTime().asMilliseconds();
						Vector2f startPosition = utils::get4sizesCoords(allLLBlocks[arrSize - 1])[1];
						Vector2f endPosition = utils::get4sizesCoords(llBlock)[0];
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, true);
					}
					window.draw(llBlock);
					window.draw(value);
				}
				break;
			case InsertOption::INDEX:
				if (insertStep >= insertIndex + 2 && insertStep <= totalInsertStep) {
					// Block
					Texture addedLLTexture;
					addedLLTexture.loadFromFile("resources/blocks/LinkedList.png");
					Sprite addedLLBlock;
					addedLLBlock.setTexture(addedLLTexture);
					addedLLBlock.setPosition(Vector2f(127 + 160 * insertIndex, 250));

					// Value
					Text value;
					value.setCharacterSize(18);
					value.setFont(font);
					value.setPosition(159 + 160 * insertIndex, 268);
					value.setString(to_string(insertValue));
					value.setFillColor(Color::Black);

					Vector2f startPosition = utils::get4sizesCoords(addedLLBlock)[1];
					Vector2f endPosition = utils::get4sizesCoords(allLLBlocks[insertIndex])[0];
					int timeStep = clock.getElapsedTime().asMilliseconds();

					if (insertStep >= insertIndex + 3) {
						Arrow arrow(startPosition, endPosition, 5, Color::Black);
						arrow.drawTo(window, timeStep, insertStep == insertIndex + 3);
					}
					window.draw(addedLLBlock);
					window.draw(value);
					if (insertStep == insertIndex + 4) {
						Vector2f startPosition2 = utils::get4sizesCoords(allLLBlocks[insertIndex - 1])[1];
						Vector2f endPosition2 = utils::get4sizesCoords(addedLLBlock)[0];
						Arrow arrow2(startPosition2, endPosition2, 5, Color::Black);
						arrow2.drawTo(window, timeStep, true);
					}
				}
				break;
			default:
				break;
			}
		}

		// Draw Head/Tail
		if (arrSize == 1) {

			Vector2f firstCenter = Vector2f(allLLBlocks[0].getPosition().x + allLLBlocks[0].getGlobalBounds().width / 2,
				allLLBlocks[0].getPosition().y + allLLBlocks[0].getGlobalBounds().height / 2);

			Text head("Head/Tail", font, 20);
			head.setFillColor(Color::Red);
			head.setPosition(firstCenter.x - head.getGlobalBounds().width / 2, firstCenter.y + 50);
			window.draw(head);
		}
		else if (arrSize > 1) {
			Vector2f firstCenter = Vector2f(allLLBlocks[0].getPosition().x + allLLBlocks[0].getGlobalBounds().width / 2,
				allLLBlocks[0].getPosition().y + allLLBlocks[0].getGlobalBounds().height / 2);

			Vector2f lastCenter = Vector2f(allLLBlocks[arrSize - 1].getPosition().x + allLLBlocks[arrSize - 1].getGlobalBounds().width / 2,
				allLLBlocks[arrSize - 1].getPosition().y + allLLBlocks[arrSize - 1].getGlobalBounds().height / 2);

			Text head("Head", font, 20);
			head.setFillColor(Color::Red);
			head.setPosition(firstCenter.x - head.getGlobalBounds().width / 2, firstCenter.y + 40);

			Text tail("Tail", font, 20);
			tail.setFillColor(Color::Red);
			tail.setPosition(lastCenter.x - tail.getGlobalBounds().width / 2, lastCenter.y + 40);

			window.draw(head);
			window.draw(tail);
		}
	}
}


CircularLL::~CircularLL() {}