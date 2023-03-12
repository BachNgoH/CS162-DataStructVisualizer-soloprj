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