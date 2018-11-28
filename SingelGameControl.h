#pragma once
#include "GameControl.h"
class SingelGameControl :
	public GameControl
{
public:
	SingelGameControl();
	~SingelGameControl();


private:
	int EnemyCount;
	int EnemyKilledCount;
	int EnemyProducedCount;

};

