#pragma once
class GraphicControl
{
public:
	GraphicControl() :ScreenSizeX(1280),
		ScreenSizeY(720){}
	~GraphicControl();

	int ReferScreenSizeX() { return ScreenSizeX; }
	int ReferScreenSizeY() { return ScreenSizeY; }
	
private:
	int ScreenSizeX;
	int ScreenSizeY;
};

