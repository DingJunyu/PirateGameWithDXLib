#pragma once
#include"DxLib.h"
class GameControl
{
public:
	GameControl();
	~GameControl();
	
	/*���g�ύX�֐�*/
	void SetACount(int A) { TeamACount = A; }
	void SetBCount(int B) { TeamBCount = B; }

	void SetStartTime() { StartTime = GetNowCount(); }


	/*�₢���킹�֐�*/
	int ReferPassedTime() { return (NowTime - StartTime)/1000; }
	int ReferACount() { return TeamACount; }
	int ReferBCount() { return TeamBCount; }
	/*������̃`�[�����S�ł̏ꍇ*/
	bool GameOver() { return (TeamACount <= 0 || TeamBCount <= 0); }
	/*A�`�[�������ꍇ��false�A����true*/
	bool Winner() { return TeamACount <= 0; }

protected:
	int TeamACount;
	int TeamBCount;
	int StartTime;
	int NowTime;
	int ATeamShootCount;
	int BTeamShootCount;
};

