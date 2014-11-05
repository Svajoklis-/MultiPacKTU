#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	playing = false; 
	coords.x = 8; 
	coords.y = 8;
	coords.way = Top;
	next = Top; 
	score = 666;
	lives = 3;
}

void Player::MakeAMove(bool currentisvalid, bool nextisvalid){
	if (nextisvalid) coords.way = next;
	else if (!currentisvalid) return;
	switch (coords.way){
	case Top:
		coords.y--;
		break;
	case Right:
		coords.x++;
		break;
	case Bottom:
		coords.y++;
		break;
	case Left:
		coords.x--;
		break;
	}
}