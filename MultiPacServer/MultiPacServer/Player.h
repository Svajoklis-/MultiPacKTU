#include "SDL_net.h"
#include "Entity.h"

class Player : public Entity{
private:
	TCPsocket socket;
	bool playing;
	int score;
	int lives;

public:

	Player(TCPsocket socket);

	TCPsocket GetSocket() { return socket; }
	int GetScore(){ return score; }
	int GetLives(){ return lives; }
	bool IsPlaying() { return playing; }

	void SetPlaying(bool playing) { this->playing = playing; }
	void IncScore(){ score++; }
	void SetScore(int score){ this->score = score; }

	~Player() { SDLNet_TCP_Close(socket); }
};