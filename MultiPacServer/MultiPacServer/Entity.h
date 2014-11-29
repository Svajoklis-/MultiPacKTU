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
	Way GetNextWay();
	Coords GetCoords();
	int GetSpeed();

	void SetNextWay(Way next);
	void SetCoords(Coords coords);

	virtual void MakeAMove(bool currentisvalid, bool nextisvalid);

	static Way ReverseWay(Way input);
	static int ManhattansDistance(Coords from, Coords to);
	static Coords CoordsAfterMoving(Entity *entity, int turns);
};

#endif