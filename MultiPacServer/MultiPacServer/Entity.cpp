#include "Entity.h"
#include <stdlib.h> 

void Entity::MakeAMove(bool currentisvalid, bool nextisvalid){
	if (nextisvalid) coords.way = next;
	else if (!currentisvalid) return;
	switch (coords.way){
	case Top:
		coords.y --;
		break;
	case Right:
		coords.x ++;
		break;
	case Bottom:
		coords.y ++;
		break;
	case Left:
		coords.x --;
		break;
	}
}

Entity::Way Entity::GetNextWay() { return next; }

Entity::Coords Entity::GetCoords() { return coords; }

int Entity::GetSpeed(){ return speed; }

void Entity::SetNextWay(Way next) { this->next = next; }

void Entity::SetCoords(Coords coords) { this->coords = coords; }

Entity::Way Entity::ReverseWay(Way input){
	switch (input){
	case Top: return Bottom;
	case Right: return Left;
	case Bottom: return Top;
	case Left: return Right;
	}
	return Top;
}

int Entity::ManhattansDistance(Coords from, Coords to){
	return abs(from.x - to.x) + abs(from.y - to.y);
}

Entity::Coords Entity::CoordsAfterMoving(Coords coords, int distance){
	switch (coords.way){
	case Top:
		coords.y -= distance;
		break;
	case Right:
		coords.x += distance;
		break;
	case Bottom:
		coords.y += distance;
		break;
	case Left:
		coords.x -= distance;
		break;
	}
	return coords;
}