#pragma once
#include"DxLib.h"
class FrameControl
{
public:
	FrameControl() :
		FRAMES_PER_SECOND(60),
		SKIP_TICKS(1000 / FRAMES_PER_SECOND),
	    next_game_tick(GetTickCount()),
		sleep_time(10) {}
	~FrameControl();

	void Wait();

private:
	const int FRAMES_PER_SECOND;
	const int SKIP_TICKS;
	DWORD next_game_tick;
	int sleep_time;
};

