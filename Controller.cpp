#include "Controller.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

int Controller::GetOrder() {
	GetHitKeyStateAll(KeyBuf);
	/*進行コントロール*/
	if (KeyBuf[KEY_INPUT_UP])
		return CONTROL::UP;
	if (KeyBuf[KEY_INPUT_DOWN])
		return CONTROL::DOWN;
	if (KeyBuf[KEY_INPUT_RIGHT])
		return CONTROL::RIGHT;
	if (KeyBuf[KEY_INPUT_LEFT])
		return CONTROL::LEFT;

	/*射撃コントロール*/
	if (KeyBuf[KEY_INPUT_Z] && GetInputChar(TRUE))
		return CONTROL::LEFT_SHOOT;
	if (KeyBuf[KEY_INPUT_C] && GetInputChar(TRUE))
		return CONTROL::RIGHT_SHOOT;
	if (KeyBuf[KEY_INPUT_X] && GetInputChar(TRUE))
		return CONTROL::ALL_SHOOT;

	/*ゲームコントロール*/
	if (KeyBuf[KEY_INPUT_ESCAPE])
		return CONTROL::ESC;
	if (KeyBuf[KEY_INPUT_RETURN])
		return CONTROL::ENTER;

	/*それ以外は空を返す*/
	return CONTROL::EMPTY;
}