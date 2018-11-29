#include "MainGameProgress.h"

MainGameProgress::~MainGameProgress()
{
}

void MainGameProgress::ErrorCheck() {
	int Count;
	if (Title)Count++;
	if (GameOver)Count++;
	if (SingleGameProcessing)Count++;
	if (MainMenu)Count++;
	if (Setting)Count++;
	if (Help)Count++;
	if(Count!=1){}
		//‚±‚±‚ÍƒGƒ‰[ˆ—
}