#include "./list.h"
#include "./fatal.h"

struct Node
{
    int Element;
    Position Next;
};

List MakeEmpty(List L)
{
    if (L)
    {
        DeleteList(L);
    }
    L = malloc(sizeof(struct Node));
    if (L == NULL)
    {
        FatalError("Out of memeory!");
    }
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P, List L)
{
    return !IsEmpty(L) && P->Next == NULL;
}

Position Find(int X, List L)
{
    Position P;

    P = L->Next;
    while (P != NULL && P->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void Delete(int X, List L)
{
    Position P, TmpCell;

    P = L->Next;
    while (P != NULL && P->Next->Element != X)
    {
        P = P->Next;
    }
    TmpCell = P->Next;
    P->Next = TmpCell->Next;
    free(TmpCell);
}

Position FindPrevious(int X, List L)
{
    Position P;

    P = L->Next;
    while (P != NULL && P->Next->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void Insert(int X, List L, Position P)
{
    Position TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if (!TmpCell)
    {
        FatalError("Out of Space!");
    }

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Position P, Tmp;

    P = L->Next;
    L->Next = NULL;
    while (P != NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
    return P->Next;
}

int Retrieve(Position P)
{
    return P->Element;
}

void PrintList(List L)
{
    int i = 1;
    Position P = Header(L);

    if (IsEmpty(L))
    {
        printf("Empty list.\n");
    }
    else
    {
        do
        {
            P = Advance(P);
            printf("第%d个元素是%d\n", i, Retrieve(P));
            i++;
        } while (!IsLast(P, L));
    }
}