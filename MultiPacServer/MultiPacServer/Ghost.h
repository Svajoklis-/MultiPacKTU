#include "Entity.h"

class Ghost : public Entity{
public:
	static const int homex = 80;
	static const int homey = 104;
	static const int frightimer = 350; //~10 secs
	static const int flashtimer = 50;
	enum Personality{ Blinky, Pinky, Inky, Sue, FrightBlue, FrightWhite, Eyes };

private:
	Personality type;
	Personality current;
	Coords target;
	int frightened;

	int ManhattansDistance(Coords from, Coords to);

public:
	Ghost(Personality type);

	Personality GetPersonality();
	void SetPersonality(Personality person);

	void Frighten();
	void MakeAMove(bool currentisvalid, bool nextisvalid);

	void Tick();
};