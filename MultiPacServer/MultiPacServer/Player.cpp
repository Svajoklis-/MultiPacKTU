#include "Player.h"

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