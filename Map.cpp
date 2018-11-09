#include "Map.h"

Tree::Tree(int LV) {
	Level = LV;
	if (LV == 1)
		Top = true;
	else
		Top = false;
	if (LV == 4)
		Bottom = true;
	else
		Bottom = false;
}