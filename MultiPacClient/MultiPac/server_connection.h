#include <SDL_net.h>
#include <thread>

#ifndef H_SERVER_CONNECTION
#define H_SERVER_CONNECTION

enum packet_enum{
	NOP = 0,
	NEW_GAME = 10,			//send map and stuff
	READY = 11,				//loaded everything
	MESSAGEOFTHEDAY = 12,
	GETCOORDS = 15,
	GOINGTOP = 20,
	GOINGRIGHT = 21,
	GOINGBOTTOM = 22,
	GOINGLEFT = 23,
	EXITGAME = 25,
	DISCONNECT = 30
};

class Server_connection{
	char* connectionstring = "localhost";
	int port = 2001;
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	const char* error;

public:
	Server_connection();
	int get_code(int code);
	void get_coords(int *num, int *ping);
	~Server_connection();

private:
	void thread_get_coords(int *num, int *ping);
	bool getting_coords = false;
};

#endif