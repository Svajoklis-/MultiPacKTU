#include "Ghost.h"

Ghost::Ghost() {
	coords.x = 80;
	coords.y = 80;
	coords.way = Top;
	next = Top;
	speed = 2;
}