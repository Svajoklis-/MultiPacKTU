#include "SDL_net.h"

class Player{
public:
	enum Way{ Top, Right, Bottom, Left };
	struct Coords{ int x; int y; };

private:
	TCPsocket socket;
	Way current, next;	//mutexezz needed
	Coords coords;		//mutex needed
	bool playing;

public:

	Player(TCPsocket socket);

	TCPsocket GetSocket() { return socket; }
	Way GetNextWay() { return next; }
	Coords GetCoords() { return coords; }
	bool IsPlaying() { return playing; }

	void SetNextWay(Way next) { this->next = next; }
	void SetCoords(Coords coords) { this->coords = coords; }
	void SetPlaying(bool playing) { this->playing = playing; }

	~Player() { SDLNet_TCP_Close(socket); }

	void MakeAMove(bool nextisvalid);
};