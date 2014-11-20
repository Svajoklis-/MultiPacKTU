#include "SDL_net.h"
#include "Entity.h"

class Player : public Entity{
public:
	static const int startingx = 80;
	static const int startingy = 120;
private:
	TCPsocket socket;
	bool playing;
	int inactive;
	int score;
	int lives;

public:

	Player(TCPsocket socket);

	TCPsocket GetSocket() { return socket; }
	int GetScore(){ return score; }
	int GetLives(){ return lives; }
	bool IsPlaying() { return playing; }
	bool IsInactive() { return inactive > 0; }

	void SetPlaying(bool playing) { this->playing = playing; }
	void SetInactive(){ inactive = 20; speed = 4; }
	void IncScore(){ score++; }
	void SetScore(int score){ this->score = score; }

	void MakeAMove(bool currentisvalid, bool nextisvalid);

	~Player() { SDLNet_TCP_Close(socket); }
};