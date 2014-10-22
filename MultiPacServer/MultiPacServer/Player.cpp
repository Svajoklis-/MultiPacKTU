#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	playing = false; 
	coords.x = 8; 
	coords.y = 8; 
	next = Top; 
}

void Player::MakeAMove(bool nextisvalid){
	if (nextisvalid) coords.way = next;
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