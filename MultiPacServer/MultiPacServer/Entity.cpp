#include "Entity.h"

void Entity::MakeAMove(bool currentisvalid, bool nextisvalid){
	if (nextisvalid) coords.way = next;
	else if (!currentisvalid) return;
	switch (coords.way){
	case Top:
		coords.y -= speed;
		break;
	case Right:
		coords.x += speed;
		break;
	case Bottom:
		coords.y += speed;
		break;
	case Left:
		coords.x -= speed;
		break;
	}
}