#include "Ghost.h"

Ghost::Ghost(Personality type) {
	coords.way = Top;
	next = Top;
	frightened = 0;
	this->type = type;
	this->current = type;
	switch (current)
	{
	case Ghost::Blinky:
		coords.x = 80;
		coords.y = 80;
		break;
	case Ghost::Pinky:
		coords.x = 80;
		coords.y = 104;
		break;
	case Ghost::Inky:
		coords.x = 80;
		coords.y = 96;
		break;
	case Ghost::Sue:
		coords.x = 80;
		coords.y = 112;
		break;
	}
	speed = 2;
}

Ghost::Personality Ghost::GetPersonality(){ return current; }

void Ghost::SetPersonality(Personality person){
	current = person;
	switch (current)
	{
	case Ghost::Blinky:
	case Ghost::Pinky:
	case Ghost::Inky:
	case Ghost::Sue:
		frightened = 0;
		speed = 2;
		break;
	case Ghost::FrightBlue:
	case Ghost::FrightWhite:
		speed = 1;
		break;
	case Ghost::Eyes:
		frightened = 0;
		speed = 3;
		break;
	}
}

void Ghost::MakeAMove(bool currentisvalid, bool nextisvalid){
	Entity::MakeAMove(currentisvalid, nextisvalid);
	if (coords.x == homex && coords.y == homey && current == Eyes){ //if its at home dead reset personality
		current = type;
		speed = 2;
	}
}

void Ghost::Frighten(){ frightened = frightimer; }

void Ghost::Tick(){
	if (frightened > 0){
		frightened--;
		if (frightened == 0){
			current = type;
			speed = 2;
		}
	}
	if (frightened > 0 && frightened < flashtimer){
		if (current == FrightBlue) current = FrightWhite;
		else current = FrightBlue;
	}
}