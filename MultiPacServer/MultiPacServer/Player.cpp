#include "Player.h"

Player::Player(TCPsocket socket) { 
	this->socket = socket; 
	dead = -1; 
	coords.x = startingx; 
	coords.y = startingy;
	coords.way = Top;
	next = Top; 
	score = 0;
	lives = 3;
	speed = 2;
	inactive = 0;
}

void Player::SetPlaying(bool playing){
	if (playing) this->dead = 0;
	else this->dead = -1;
}

void Player::Tick(){
	if (inactive > 0){
		inactive--;
		if (inactive == 5) speed -= 2;
	}
	if (dead > 0){
		dead--;
	}
}

TCPsocket Player::GetSocket() { return socket; }

int Player::GetScore(){ return score; }

int Player::GetLives(){ return lives; }

bool Player::IsAlive() { return dead == 0; }

bool Player::IsActive() { return inactive == 0; }

void Player::IncScore(int score){ this->score += score; }

void Player::SetScore(int score){ this->score = score; }

void Player::MakeAMove(bool currentisvalid, bool nextisvalid){
	if (inactive > 0){
		if (currentisvalid){
			Entity::MakeAMove(currentisvalid, false);
			return;
		}
		else{
			inactive = 0;
			speed = 2;
		}
	}
	if (coords.x == 80 && coords.y == 80 && next == Bottom) nextisvalid = false;	//no acces to ghosthouse
	Entity::MakeAMove(currentisvalid, nextisvalid);
}

void Player::Kill(){
	if (lives == 0){
		dead = -1;
		return;
	}
	dead = dietime;
	lives--;
	coords.x = startingx;
	coords.y = startingy;
	coords.way = Top;
	next = Top;
}

void Player::Deactivate(){
	inactive = inactiftime; 
	speed = inactifspeed;
}

Player::~Player() { SDLNet_TCP_Close(socket); }