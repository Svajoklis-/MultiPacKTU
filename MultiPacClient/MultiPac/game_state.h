#ifndef H_GAME_STATE
#define H_GAME_STATE

enum game_states
{
	st_exit,
	st_null
};

class Game_state
{
public:
	virtual void events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Game_state(){};

	game_states get_state(){ return state; };

protected:
	game_states state = st_null;
};

#endif // H_GAME_STATE

