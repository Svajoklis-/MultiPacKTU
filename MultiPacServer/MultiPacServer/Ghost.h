#include "Entity.h"

class Ghost : public Entity{
public:
	enum Personality{ Blinky, Pinky, Inky, ClydeorSue };	//originaliam tai Clyde

private:
	Personality type;
	Coords target;
	bool frightened;

	int ManhattansDistance(Coords from, Coords to);

public:
	Ghost(Personality person);

	Personality GetPersonality(){ return type; }

	void Think();

	void Frighten(){ frightened = true; }
	void MakeNormal(){ frightened = false; }
};