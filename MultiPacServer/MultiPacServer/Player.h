#include "SDL_net.h"
#include "Entity.h"

class Player : public Entity{
public:
	static const int startingx = 80;
	static const int startingy = 120;
private:
	static const int dietime = 150; //~6 secs
	static const int inactiftime = 20;
	static const int inactifspeed = 4;

	TCPsocket socket;
	int dead;		//isnt participating in the game
	int inactive;	//cant control
	int score;
	int lives;

public:

	Player(TCPsocket socket);

	TCPsocket GetSocket();
	int GetScore();
	int GetLives();
	bool IsAlive();
	bool IsActive();

	void SetPlaying(bool playing);
	void IncScore(int score);
	void SetScore(int score);

	void MakeAMove(bool currentisvalid, bool nextisvalid);
	void Tick();
	void Kill();
	void Deactivate();

	~Player();
};