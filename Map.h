#pragma once
#include"ShipUniversal.h"
#include"Weapon.h"
/**/
class Map
{
public:
	Map();
	
private:

	ShipUniversal * ShipsHere[10];
	Ammo * AmmoHere[50];
};

class Tree {
public:
	Tree();
	Tree(int LV);

	Tree *
	
private:
	int Level;
	bool Top;
	bool Bottom;
	Tree *Father;
	Tree *UL;
	Tree *UR;
	Tree *LR;
	Tree *LL;
	Map Here;
};