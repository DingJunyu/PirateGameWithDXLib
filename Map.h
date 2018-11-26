#pragma once
#include"ShipUniversal.h"
#include"Weapon.h"
#include"MapObject.h"
#include<list>

enum SON_NODE_TYPE {
	SHIP = 0,
	AMMO,
	MAP_OBJECT
};

class Tree {
public:
	friend Tree * ConstructMap();

	Tree() :Top(false), Bottom(false) {}
	Tree(bool T) :Top(T),Depth(0),Bottom(false) {}
	Tree(int Dth) :Depth(Dth), Top(false), Bottom(Dth == 5) {}

	/*�\���֐�*/
	Tree * Build();
	/*����֐�*/
	bool FreeMemory();

	/*�f�[�^����֐�*/
	void InsertShip(ShipUniversal Target);
	void InsertAmmo(Ammo Target);
	void InsertObject(MapObject Target);

	void DeleteShip(ShipUniversal Target);
	void DeleteAmmo(Ammo Target);
	void DeleteObject(MapObject Target);

	/*�₢���킹�֐�*/

	
private:
	int Depth;
	bool Top;
	bool Bottom;
	Tree *ChildNode[4];

	int CountOfShip;
	int CountOfAmmo;
	int CountOfMapObject;

	std::list<ShipUniversal> ShipList;
	std::list<Ammo> AmmoList;
	std::list<MapObject> MapObjectList;
};

Tree * ConstructMap();