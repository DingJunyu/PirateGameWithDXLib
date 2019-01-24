#pragma once
class MainGameProgress
{
public:
	MainGameProgress():
		Title(true),GameOver(false),SingleGameProcessing(false),
		MainMenu(false),Setting(false),Help(false){}
	~MainGameProgress();

	/*‘€ìŠÖ”*/
	void SingleGameStart() { SingleGameProcessing = true; }
	void MoveToSetting() { Setting = true; }

	/*ƒGƒ‰[*/
	void ErrorCheck();

private:
	bool Title;
	bool GameOver;
	bool SingleGameProcessing;
	bool MainMenu;
	bool Setting;
	bool Help;
};