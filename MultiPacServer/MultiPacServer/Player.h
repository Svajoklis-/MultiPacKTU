#include "SDL_net.h"

class Player{
public:
	enum Way{ Top, Right, Bottom, Left };
	struct Coords{ int x; int y; };

private:
	TCPsocket socket;
	Way current, next;	//mutexezz needed
	Coords coords;		//mutex needed

public:
	Player(TCPsocket socket) { this->socket = socket; }

	TCPsocket GetSocket() { return socket; }

	void SetNextWay(Way next) { this->next = next; }

	Coords GetCoords() { return coords; }

	void MakeAMove(bool nextisvalid);

	~Player() { SDLNet_TCP_Close(socket); }

};