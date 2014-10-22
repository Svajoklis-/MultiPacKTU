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
	GOINGTOP = 20,
	GOINGRIGHT = 21,
	GOINGBOTTOM = 22,
	GOINGLEFT = 23,
	EXITGAME = 25,
	DISCONNECT = 30
};

class Server_connection{
public:
	enum Way{ Right, Bottom, Left, Top };
	struct Coords{ int x; int y; Way way; };
	static const int mapheight = 27;
	static const int mapwidth = 21;

private:
	char* connectionstring = "localhost";
	int port = 2001;
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */

public:
	Server_connection();
	void new_game(int map[][mapwidth]);
	void ready();
	void going_top();
	void going_bottom();
	void going_right();
	void going_left();
	void exit_game();
	void disconnect(){ send_code(DISCONNECT); }
	void get_coords(Coords *coords, int *count, int *ping);		//isoreje turi coords masyva, int count ir int ping taip kaip tu darei
	~Server_connection();

private:

	void send_code(int code);

	void thread_get_coords(Coords *coords, int *count, int *ping);
	bool getting_coords = false;
};

#endif