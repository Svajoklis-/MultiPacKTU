#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	playing = false; 
	coords.x = startingx; 
	coords.y = startingy;
	coords.way = Top;
	next = Top; 
	score = 0;
	lives = 3;
	speed = 2;
	inactive = 0;
}

void Player::MakeAMove(bool currentisvalid, bool nextisvalid){
	if (inactive > 0){
		if (currentisvalid){
			Entity::MakeAMove(currentisvalid, false);
			inactive--;
			if (inactive == 5) speed -= 2;
			return;
		}
		else{
			inactive = 0;
			speed = 2;
		}
	}
	Entity::MakeAMove(currentisvalid, nextisvalid);
}