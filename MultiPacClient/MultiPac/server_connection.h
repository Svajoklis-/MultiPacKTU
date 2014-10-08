#include <SDL_net.h>

#ifndef H_SERVER_CONNECTION
#define H_SERVER_CONNECTION

enum packet_enum{
	NOP = 0,
	NEW_GAME = 10,			//send map and stuff
	READY = 11,				//loaded everything
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
	int get_coords();
	~Server_connection();
};

#endif