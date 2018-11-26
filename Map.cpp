#include "Map.h"
/*Ä‹A‚Å–Ø‚ð¶¬*/
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

/*–Ø¶¬ŠÖ”*/
Tree * ConstructMap() {
	Tree *Here = new Tree(true);
	return Here;
}

/*ƒƒ‚ƒŠ‰ð•úŠÖ”*/
/*Ž¸”s‘Î‰ž‚È‚µ*/
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