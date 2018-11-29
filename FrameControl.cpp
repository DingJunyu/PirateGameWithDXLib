#include "FrameControl.h"

FrameControl::~FrameControl()
{
}

void FrameControl::Wait() {
	next_game_tick += SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0)
	{
		Sleep(sleep_time);
	}
}