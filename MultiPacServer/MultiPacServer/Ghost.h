#include "Entity.h"

class Ghost : public Entity{
public:
	enum Personality{ Blinky, Pinky, Inky, ClydeorSue };	//originaliam tai Clyde
private:
	Personality type;

public:
	Ghost();

	Personality GetPersonality(){ return type; }
};