#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	playing = false; 
	coords.x = 0; 
	coords.y = 0; 
	next = Top; 
}

void Player::MakeAMove(bool nextisvalid){
	if (nextisvalid) current = next;
	switch (current){
	case Top:
		coords.x--;
		break;
	case Right:
		coords.y++;
		break;
	case Bottom:
		coords.x++;
		break;
	case Left:
		coords.y--;
		break;
	}
}