#include <SDL_net.h>
#include <thread>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <chrono>
#include "timer.h"

#ifndef H_SERVER_CONNECTION
#define H_SERVER_CONNECTION

//Bendra ivykiu schema:

//konstruktorius - prisijungiama prie serverio (sitas kolkas lus jeigu neis padaryt rysio)
//new game -> gauni map (sitas turbut niekad nelus, nebent nera rysio)
//klientas patvirtina kad yra pasiruoses pradeti: ready (panasiai kaip 'loading' jeigu tau reiketu ilgiau uzkraudineti ivairius resursus) -> prasideda zaidimas (anksciau negu newgame nepatartina, nes nesutaps mapai ant servo ir kliento)
//getcoords -> gauni visu objektu koordinates (tik po ready, kitaip lus servas)p.s. threadus pats pasitvarkysi tikriausiai vieninteliam sitam reikia nes "render speed > ping-ish" 
//goingXXXXXX -> serveriui siunciama busima zaidejo kryptis (sitas turbut niekad nelus, nebent nera rysio)
//exitgame -> isemamas is einamojo zaidimo taciau rysys dar yra palaikomas (tik po ready nes lus)
//destruktorius -> atsijungiama nuo serverio (sitas turbut niekad nelus, nebent nera rysio)

enum packet_enum{
	NOP = 0,
	NEW_GAME = 10,			//send map and stuff
	READY = 11,				//loaded everything
	MESSAGEOFTHEDAY = 12,
	GETCOORDS = 15,
	GETMAP = 16,
	GETSCORE = 17,
	GETSTATEPACKET = 18,	//future is here
	GOINGTOP = 20,
	GOINGRIGHT = 21,
	GOINGBOTTOM = 22,
	GOINGLEFT = 23,
	RESETDIR = 24,		//atstato pasirinkta krypti (onkeypress-"go x way", keyrelease-"reset direction")
	EXITGAME = 25,
	DISCONNECT = 30
};

class Server_connection{
public:
	static const int mapheight = 27;
	static const int mapwidth = 21;
	static const int maxplayercount = 4;
	static const int maxghostcount = 8;
	enum Way{ Right, Bottom, Left, Top };
	struct Coords{ int x; int y; Way way; };
	struct State_Packet{
		int player_count;
		int ghost_count;
		int score;
		int lives;
		Coords players[maxplayercount];
		Coords ghosts[maxghostcount];
		int map[mapheight][mapwidth];
	};
	
private:
	//char* connectionstring = "localhost";
	char *connectionstring = "localhost";
	int port = 2001;
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	SDLNet_SocketSet set;

public:
	Server_connection();
	void new_game(int *map);
	void ready();
	void going_top();
	void going_bottom();
	void going_right();
	void going_left();
	void exit_game();
	void disconnect(){ send_code(DISCONNECT); }

	void get_coords(Coords *coords, int *count, int *ping);		//isoreje turi coords masyva, int count ir int ping taip kaip tu darei
	void get_state_packet(State_Packet *data, int *ping);

	void dir_reset(){ send_code(RESETDIR); }
	~Server_connection();

private:
	void send_code(int code);
	bool getting_coords = false;
};

#endif