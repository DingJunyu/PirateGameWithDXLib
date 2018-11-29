#pragma once
#include "GameControl.h"
class SingleGameControl :
	public GameControl
{
public:
	SingleGameControl();
	~SingleGameControl();


private:
	int EnemyCount;
	int EnemyKilledCount;
	int EnemyProducedCount;

};

