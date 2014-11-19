#include "Ghost.h"
#include <stdlib.h> 

Ghost::Ghost(Personality type) {
	coords.x = 80;
	coords.y = 80;
	coords.way = Top;
	next = Top;
	speed = 2;
	this->type = type;
}

int Ghost::ManhattansDistance(Coords from, Coords to){
	return abs(from.x - to.x) + abs(from.y - to.y);
}

void Ghost::Think(){

}