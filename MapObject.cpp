#include "MapObject.h"

MapObject::~MapObject()
{
}

void MapObject::FreeMemory() {
	for (int i = 0; i < CollisionCount; ++i)
		delete[] Collision[i];
	delete[] Collision;
}


void MapObject::ReadCollision(FILE *FLPointer) {
	GetGraphSize(*MapHandle, &Width, &Length);

	fscanf_s(FLPointer, "%lf", &CoordX);
	fscanf_s(FLPointer, "%lf", &CoordY);
	fscanf_s(FLPointer, "%lf", &Radian);
	for (int i = 0; i < CollisionCount; ++i) {
		fscanf_s(FLPointer, "%lf", &Collision[i][1]);
		fscanf_s(FLPointer, "%lf", &Collision[i][2]);
		fscanf_s(FLPointer, "%lf", &Collision[i][3]);
	}
}

void MapObject::Cal() {
	SinSaved = sin(Radian);
	CosSaved = cos(Radian);
	for (int i = 0; i < CollisionCount; i++) {
		Collision[i][COLLISION::REAL_COORD_X] =
			Collision[i][COLLISION::COORD_X] * CosSaved
			- Collision[i][COLLISION::COORD_Y] * SinSaved
			+CoordX;
		Collision[i][COLLISION::REAL_COORD_Y] =
			Collision[i][COLLISION::COORD_Y] * CosSaved
			+ Collision[i][COLLISION::COORD_X] * SinSaved
			+CoordY;
		/*Œã‚ÅŽg‚¤*/
/*		AbsShadowCenterX = ShadowCenterX * ShipCos
			- ShadowCenterY * ShipSin;
		AbsShadowCenterY = ShadowCenterY * ShipCos
			+ ShadowCenterX * ShipSin;*/
	}
}

void MapObject::Show(double X,double Y) {
	DrawRotaGraph3((int)(CoordX - X), (int)(CoordY - Y),
		(int)(Width / 2), (int)(Length / 2),
		ZOOM_MULTIPLE, ZOOM_MULTIPLE,
		Radian, *MapHandle, TRUE, FALSE);
	/*
	unsigned int Cr = GetColor(0, 250, 0);
	for (int i = 0; i < CollisionCount; i++) {
		DrawCircle(Collision[i][COLLISION::REAL_COORD_X] - X,
			Collision[i][COLLISION::REAL_COORD_Y] - Y,
			Collision[i][COLLISION::RADIUS], Cr, FALSE);
	}
	*/
}

void MapObject::TEST() {
	GetGraphSize(*MapHandle, &Width, &Length);
	CoordX = 500;
	CoordY = 500;
	Collision[0][0] = 15; Collision[0][1] = 15; Collision[0][2] = 50;
	Collision[1][0] = -20; Collision[1][1] = 0; Collision[1][2] = 50;
	Collision[2][0] = 10; Collision[2][1] = -15; Collision[2][2] = 50;
	Cal();
}