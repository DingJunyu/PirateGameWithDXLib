#pragma once
#include"MathDefine.h"
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include"DxLib.h"

class MapObject
{
public:
	MapObject(int CoCount, int *Hdle) :CollisionCount(CoCount),
		MapHandle(Hdle)
	{
		for (int i = 0; i < CollisionCount; ++i)
			Collision[i] = new double[5];
	}
	~MapObject();

	/*�g���I�������K���g���I�I�I�I�I�I�I�I�I�I�I*/
	void FreeMemory();

	/*���g�ύX�֐�*/
	void ReadCollision(FILE *FLPointer);
	void Cal();
	void Show(double X, double Y);

	/*�e�X�g�p�֐�*/
	void TEST();

	/*�₢���킹�֐�*/
	int ReferColCount() { return CollisionCount; }
	double ReferColR(int i) { return Collision[i][2]; }
	double ReferColRX(int i) { return Collision[i][3]; }
	double ReferColRY(int i) { return Collision[i][4]; }
	bool ReferUsable();

private:
	const int *MapHandle; 
	int Width, Length;
	double CoordX;
	double CoordY;
	double Radian;
	double SinSaved;
	double CosSaved;

	const int CollisionCount;//�~�̐�
	double **Collision = new double*[CollisionCount];
	//�~��X���W�AY���W�A���a�A����X���W�A����Y���W
};

