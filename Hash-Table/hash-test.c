#include "hash.h"
#include <stdio.h>

#define NumItems 400

int main(void)
{
	HashTable H;
	Position P;
	int i;
	int j;
	int CurrentSize = 13;

	H = InitializeTable(CurrentSize);

	for (i = 0, j = 0; i < NumItems; i++, j += 71)
	{
		Insert(j, H);
	}

	MakeEmpty(H);

	for (i = 0, j = 0; i < NumItems; i++, j += 71)
	{
		Insert(j, H);
	}

	for (i = 0, j = 0; i < NumItems; i++, j += 71)
		if ((P = Find(j, H)) == NULL || Retrieve(P) != j)
			printf("Error at %d\n", j);

	for (i = 0, j = 0; i < NumItems; i++, j += 71)
	{
		Delete(j, H);
	}

	printf("TableSize: %d\n", H->TableSize);
	DestroyTable(H);

	printf("End of program.\n");
	return 0;
}
