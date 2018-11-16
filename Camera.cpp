#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

//カメラの中心点の位置を取る
void Camera::GetPos(double X, double Y) {
	CameraX = SCREEN_X / 2;
	CameraY = SCREEN_Y / 2;
	PrintoutStartX = X - SCREEN_X / 2;
	PrintoutStartY = Y - SCREEN_Y / 2;
	/*特殊状況*/
	if (X < SCREEN_X / 2) {
		CameraX = X;
		PrintoutStartX = 0;
	}
	if (X >= BOARDER_X - SCREEN_X / 2) {
		CameraX = (int)(X-BOARDER_X+SCREEN_X) % SCREEN_X;
		PrintoutStartX = BOARDER_X - SCREEN_X;
	}
	if (Y < SCREEN_Y / 2) {
		CameraY = Y;
		PrintoutStartY = 0;
	}
	if (Y >= BOARDER_Y - SCREEN_Y / 2) {
		CameraY = (int)(Y-BOARDER_Y+SCREEN_Y) % SCREEN_Y;
		PrintoutStartY = BOARDER_Y - SCREEN_Y;
	}
}

/*このものがカメラに入れるのか*/
bool Camera::TellMeShouldIShow(int X, int Y) {
	if (X >= PrintoutStartX && X <= PrintoutStartX + SCREEN_X)
		if (Y >= PrintoutStartY && Y <= PrintoutStartY + SCREEN_Y)
			return true;
	return false;
}

void Camera::ReadMapData(double X, double Y) {
	MapX = X;
	MapY = Y;
}