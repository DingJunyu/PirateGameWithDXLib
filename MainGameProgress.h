#pragma once
class MainGameProgress
{
public:
	MainGameProgress():
		Title(true),GameOver(false),SingleGameProcessing(false),
		MainMenu(false),Setting(false),Help(false){}
	~MainGameProgress();

	/*操作関数*/
	void SingleGameStart() { SingleGameProcessing = true; }
	void MoveToSetting() { Setting = true; }

	/*エラー*/
	void ErrorCheck();

private:
	bool Title;
	bool GameOver;
	bool SingleGameProcessing;
	bool MainMenu;
	bool Setting;
	bool Help;
};