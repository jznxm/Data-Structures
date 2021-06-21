#include <stdio.h>
#include "cursor.h"

int main(void)
{
	List L;
	InitializeCursorSpace();
	L = MakeEmpty(L);
	Insert(3, L, 1);
	Insert(5, L, 2);
	Insert(1, L, 3);
	Insert(2, L, 4);
	Insert(4, L, 5);
	Print(L);
	Delete(5, L);
	Print(L);
	DeleteList(L);
	Print(L);

	return 0;
}