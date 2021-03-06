#include "Map.h"
/*再帰で木を生成*/
Tree * Tree::Build() {
	if (Depth + 1 > 5)
		return NULL;
	Tree *Here = new Tree(Depth + 1);
	*Here->ChildNode[UL] = Build();
	*Here->ChildNode[UR] = Build();
	*Here->ChildNode[LR] = Build();
	*Here->ChildNode[LL] = Build();
	if (Here->ChildNode[UL] == NULL)
		return NULL;
	return Here;
}

/*木生成関数*/
Tree * ConstructMap() {
	Tree *Here = new Tree(true);
	return Here;
}

/*メモリ解放関数*/
/*失敗対応なし*/
bool Tree::FreeMemory() {
	if (Depth > 5)
		return true;
	if (ChildNode[UL]->FreeMemory())
		delete ChildNode[UL];
	if (ChildNode[UR]->FreeMemory())
		delete ChildNode[UR];
	if (ChildNode[LR]->FreeMemory())
		delete ChildNode[LR];
	if (ChildNode[LL]->FreeMemory())
		delete ChildNode[LL];
	return true;
}