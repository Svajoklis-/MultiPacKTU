#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	playing = false; 
	coords.x = 80; 
	coords.y = 120;
	coords.way = Top;
	next = Top; 
	score = 0;
	lives = 3;
	speed = 2;
}