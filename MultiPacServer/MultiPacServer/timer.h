/*
*
*	Basic timer class for time-related functions.
*
*/

#ifndef H_TIMER
#define H_TIMER

class Timer
{
public:

	// creates a stopped timer with value 0
	Timer();

	// starts timer
	void start();

	// stops timer
	void stop();

	// starts timer with predefined initial value
	void preset(int pre);

	int restart();

	// gets elapsed ticks since start
	int ticks() const;

	bool is_started() const;
	bool is_paused() const;

private:
	int start_ticks, paused_ticks;
	bool started, paused;
};

#endif // H_TIMER
