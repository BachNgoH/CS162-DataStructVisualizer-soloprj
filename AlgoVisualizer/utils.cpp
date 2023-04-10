#include "utils.h"

bool utils::isHover(Text obj, Vector2i mousePos) {
	return mousePos.x >= obj.getPosition().x
		&& mousePos.x <= (obj.getPosition().x + obj.getGlobalBounds().width)
		&& mousePos.y >= obj.getPosition().y
		&& mousePos.y <= (obj.getPosition().y + obj.getGlobalBounds().height);
}

bool utils::isHover(Sprite obj, Vector2i mousePos) {
	return mousePos.x >= obj.getPosition().x
		&& mousePos.x <= (obj.getPosition().x + obj.getGlobalBounds().width)
		&& mousePos.y >= obj.getPosition().y
		&& mousePos.y <= (obj.getPosition().y + obj.getGlobalBounds().height);
}

bool utils::isHover(RectangleShape obj, Vector2i mousePos) {
	return mousePos.x >= obj.getPosition().x
		&& mousePos.x <= (obj.getPosition().x + obj.getGlobalBounds().width)
		&& mousePos.y >= obj.getPosition().y
		&& mousePos.y <= (obj.getPosition().y + obj.getGlobalBounds().height);
}

vector<Vector2f> utils::get4sizesCoords(Sprite obj) {
	float x = obj.getPosition().x;
	float y = obj.getPosition().y;
	float width = obj.getGlobalBounds().width;
	float height = obj.getGlobalBounds().height;
	Vector2f centerLeft = {x, y + height / 2};
	Vector2f centerRight = { x + width, y + height / 2 };
	Vector2f centerTop = { x + width / 2, y };
	Vector2f centerBot = { x + width / 2, y + height };
	return { centerLeft, centerRight, centerTop, centerBot };
}
