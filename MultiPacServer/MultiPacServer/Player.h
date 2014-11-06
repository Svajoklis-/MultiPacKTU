#include "SDL_net.h"

class Player{
public:
	enum Way{ Right, Bottom, Left, Top };
	struct Coords{ int x; int y; Way way; };

private:
	TCPsocket socket;
	Way next;			//mutexezz needed
	Coords coords;		//mutex needed
	bool playing;
	int score;
	int lives;

public:

	Player(TCPsocket socket);

	TCPsocket GetSocket() { return socket; }
	Way GetNextWay() { return next; }
	Coords GetCoords() { return coords; }
	int GetScore(){ return score; }
	int GetLives(){ return lives; }
	bool IsPlaying() { return playing; }

	void SetNextWay(Way next) { this->next = next; }
	void SetCoords(Coords coords) { this->coords = coords; }
	void SetPlaying(bool playing) { this->playing = playing; }
	void IncScore(){ score++; }
	void SetScore(int score){ this->score = score; }

	~Player() { SDLNet_TCP_Close(socket); }

	void MakeAMove(bool currentisvalid, bool nextisvalid);
};