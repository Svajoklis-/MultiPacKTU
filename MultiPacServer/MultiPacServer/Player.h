class Player{
public:
	enum Way{ Top, Right, Bottom, Left };
	struct Coords{ int x; int y; };

private:
	TCPsocket socket;
	Way current, next;	//mutexezz needed
	Coords coords;		//mutex needed

public:
	Player(TCPsocket socket){
		this->socket = socket;
	}

	TCPsocket GetSocket(){
		return socket;
	}

	void SetNextWay(Way next){
		this->next = next;
	}

	Coords GetCoords(){
		return coords;
	}

	void MakeAMove(bool nextisvalid){
		if (nextisvalid) current = next;
		switch (current){
		case Top:
			coords.x--;
			break;
		case Right:
			coords.y++;
			break;
		case Bottom:
			coords.x++;
			break;
		case Left:
			coords.y--;
			break;
		}
	}

	~Player(){
		SDLNet_TCP_Close(socket);
	}

};