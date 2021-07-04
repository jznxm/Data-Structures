#include "fatal.h"
#include "hash.h"

/* Return next prime; assume N >= 10 */
static int NextPrime(int N)
{
	int i;

	if (N % 2 == 0)
		N++;
	for (;; N += 2)
	{
		for (i = 3; i * i <= N; i += 2)
			if (N % i == 0)
				goto ContOuter; /* Sorry about this! */
		return N;
	ContOuter:;
	}
}

/* Hash function for ints */
Index Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if (TableSize < MinTableSize)
	{
		Error("Table size too small");
		return NULL;
	}

	/* Allocate table */
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
		FatalError("Out of space!!!");

	H->TableSize = NextPrime(TableSize);

	/* Allocate array of lists */
	H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
	if (H->TheLists == NULL)
		FatalError("Out of space!!!");

	/* Allocate list headers */
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = malloc(sizeof(ListNode));
		if (H->TheLists[i] == NULL)
			FatalError("Out of space!!!");
		else
			H->TheLists[i]->Next = NULL;
	}

	return H;
}

void MakeEmpty(HashTable H)
{
	if (H)
		for (int i = 0; i < H->TableSize; i++)
			H->TheLists[i]->Next = NULL;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->Next;
	while (P != NULL && P->Element != Key)
		/* Probably need strcmp!! */
		P = P->Next;
	return P;
}

Position FindPrevious(ElementType Key, HashTable H)
{
	Position P;

	P = H->TheLists[Hash(Key, H->TableSize)];
	while (P->Next != NULL && P->Next->Element != Key)
		P = P->Next;

	return P;
}

void Insert(ElementType Key, HashTable H)
{
	Position Pos, NewCell;
	List L;

	Pos = Find(Key, H);
	if (Pos == NULL) /* Key is not found */
	{
		NewCell = (Position)malloc(sizeof(ListNode));
		if (NewCell == NULL)
			FatalError("Out of space!!!");
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = Key; /* Probably need strcpy! */
			L->Next = NewCell;
		}
	}
	printf("Insert: %d\n", Key);
}

void Delete(ElementType Key, HashTable H)
{
	Position Pos, TmpCell;

	Pos = FindPrevious(Key, H);
	if (Pos->Next)
	{
		TmpCell = Pos->Next;
		Pos->Next = TmpCell->Next;
		free(TmpCell);
	}
	else
	{
		printf("Didn't find element!");
	}

	printf("Delete element: %d\n", Key);
}

ElementType Retrieve(Position P)
{
	return P->Element;
}

void DestroyTable(HashTable H)
{
	int i;

	for (i = 0; i < H->TableSize; i++)
	{
		Position P = H->TheLists[i];
		Position Tmp;

		while (P)
		{
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	}

	free(H->TheLists);
	free(H);
}
