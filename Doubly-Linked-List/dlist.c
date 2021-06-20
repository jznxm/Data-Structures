#include <stdio.h>
#include <stdlib.h>
#include "fatal.h"
#include "dlist.h"

List InitialList(List L)
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
    L->Prev = NULL;
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
    while (P && P->Next->Element != X)
    {
        P = P->Next;
    }
    TmpCell = P->Next;
    P->Next = TmpCell->Next;
    TmpCell->Next->Prev = P;
    free(TmpCell);
}

Position FindPrevious(int X, List L)
{
    Position P;

    P = L->Next;
    while (P && P->Next->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void InsertAfter(int X, List L, Position P)
{
    Position TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if (!TmpCell)
    {
        FatalError("Out of Space!");
    }

    if (P->Next)
    {
        TmpCell->Element = X;
        TmpCell->Prev = P;
        TmpCell->Next = P->Next;
        P->Next = TmpCell;
        TmpCell->Next->Prev = TmpCell;
    }
    else
    {
        TmpCell->Element = X;
        P->Next = TmpCell;
        TmpCell->Prev = P;
        TmpCell->Next = NULL;
    }
}

void DeleteList(List L)
{
    Position P, Tmp;

    P = L->Next;
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

Position Tail(List L)
{
    Position Tmp;
    Tmp = L->Next;
    while (Tmp->Next)
    {
        Tmp = L->Next;
        L = L->Next;
    }
    return Tmp;
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

void PrintListBackwards(List L)
{
    int i = 1;
    Position Tmp;
    Tmp = Tail(L);
    while (Tmp->Prev)
    {
        printf("倒数第%d个元素是: %d\n", i, Tmp->Element);
        Tmp = Tmp->Prev;
        i++;
    }
}