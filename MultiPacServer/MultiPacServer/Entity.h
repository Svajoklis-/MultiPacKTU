#ifndef H_ENTITY
#define H_ENTITY

class Entity{
public:
	enum Way{ Right, Bottom, Left, Top };
	enum MapTile{ Blank, Wall, NormalPellet, PowerPellet };
	struct Coords{ int x; int y; Way way; };

protected:
	Way next;			//mutexezz needed
	Coords coords;		//mutex needed
	int speed;

public:
	Way GetNextWay() { return next; }
	Coords GetCoords() { return coords; }

	void SetNextWay(Way next) { this->next = next; }
	void SetCoords(Coords coords) { this->coords = coords; }

	virtual void MakeAMove(bool currentisvalid, bool nextisvalid);

	Way ReverseWay(Way input);
};

#endif