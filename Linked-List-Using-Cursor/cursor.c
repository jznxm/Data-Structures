#include "cursor.h"
#include <stdlib.h>
#include "fatal.h"

struct Node
{
	ElementType Element;
	Position Next;
};

struct Node CursorSpace[SpaceSize];

static Position CursorAlloc(void)
{
	Position P;

	P = CursorSpace[0].Next;
	CursorSpace[0].Next = CursorSpace[P].Next;

	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

void InitializeCursorSpace(void)
{
	int i;

	for (i = 0; i < SpaceSize; i++)
		CursorSpace[i].Next = i + 1;
	CursorSpace[SpaceSize - 1].Next = 0;
}

List MakeEmpty(List L)
{
	if (L)
		DeleteList(L);
	L = CursorAlloc();
	if (L == 0)
		FatalError("Out of memory!");
	CursorSpace[L].Next = 0;
	return L;
}

/* Return true if L is empty */
int IsEmpty(List L)
{
	return CursorSpace[L].Next == 0;
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P, List L)
{
	return CursorSpace[P].Next == 0;
}

Position Find(ElementType X, List L)
{
	Position P;

	P = CursorSpace[L].Next;
	while (P && CursorSpace[P].Element != X)
		P = CursorSpace[P].Next;

	return P;
}

/* Assume use of a header node */
void Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L)) /* Assumption of header use */
	{				   /* X is found; delete it */
		TmpCell = CursorSpace[P].Next;
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree(TmpCell);
	}
}

/* If X is not found, then Next field of returned value is 0 */
/* Assumes a header */
Position FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (CursorSpace[P].Next &&
		   CursorSpace[CursorSpace[P].Next].Element != X)
		P = CursorSpace[P].Next;

	return P;
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */
void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;

	TmpCell = CursorAlloc();
	if (TmpCell == 0)
		FatalError("Out of space!!!");

	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
	CursorSpace[P].Next = TmpCell;
}

/* Correct DeleteList algorithm */
void DeleteList(List L)
{
	Position P, Tmp;

	P = CursorSpace[L].Next; /* Header assumed */
	CursorSpace[L].Next = 0;
	while (P != 0)
	{
		Tmp = CursorSpace[P].Next;
		CursorFree(P);
		P = Tmp;
	}
}

Position Header(List L)
{
	return L;
}

Position First(List L)
{
	return CursorSpace[L].Next;
}

Position Advance(Position P)
{
	return CursorSpace[P].Next;
}

ElementType Retrieve(Position P)
{
	return CursorSpace[P].Element;
}

void Print(const List L)
{
	int i = 1;
	Position P;

	P = L;
	if (IsEmpty(L))
	{
		printf("Empty list.\n");
	}
	else
	{
		do
		{
			P = Advance(P);
			printf("第%d个元素是: %d\n", i, Retrieve(P));
			i++;
		} while (!IsLast(P, L));
	}
}
