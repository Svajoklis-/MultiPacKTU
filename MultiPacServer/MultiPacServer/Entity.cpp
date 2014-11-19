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

Entity::Way Entity::ReverseWay(Way input){
	switch (input){
	case Top: return Bottom;
	case Right: return Left;
	case Bottom: return Top;
	case Left: return Right;
	}
}