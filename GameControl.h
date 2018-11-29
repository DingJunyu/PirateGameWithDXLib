#pragma once
#include"DxLib.h"
class GameControl
{
public:
	GameControl();
	~GameControl();
	
	/*中身変更関数*/
	void SetACount(int A) { TeamACount = A; }
	void SetBCount(int B) { TeamBCount = B; }

	void SetStartTime() { StartTime = GetNowCount(); }


	/*問い合わせ関数*/
	int ReferPassedTime() { return (NowTime - StartTime)/1000; }
	int ReferACount() { return TeamACount; }
	int ReferBCount() { return TeamBCount; }
	/*いずれのチームが全滅の場合*/
	bool GameOver() { return (TeamACount <= 0 || TeamBCount <= 0); }
	/*Aチームが勝つ場合はfalse、他はtrue*/
	bool Winner() { return TeamACount <= 0; }

protected:
	int TeamACount;
	int TeamBCount;
	int StartTime;
	int NowTime;
	int ATeamShootCount;
	int BTeamShootCount;
};

