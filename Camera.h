#pragma once
#include"MathDefine.h"
class Camera
{
public:
	Camera();
	~Camera();

	/*’†g•ÏXŠÖ”*/
	void GetPos(double X, double Y);
	void ReadMapData(double X, double Y);

	/*–â‚¢‡‚í‚¹ŠÖ”*/
	bool TellMeShouldIShow(int X,int Y);
	double ReferCameraX() { return CameraX; }
	double ReferCameraY() { return CameraY; }
	double ReferPSX() { return PrintoutStartX; }
	double ReferPSY() { return PrintoutStartY; }

private:
	double CameraX;
	double CameraY;
	double MapX;
	double MapY;
	double PrintoutStartX;
	double PrintoutStartY;
};