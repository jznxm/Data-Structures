#include "fatal.h"
#include "avl-tree.h"

struct AvlNode
{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

static int Height(Position P)
{
    if (P == NULL)
        return -1;
    else 
        return P->Height;
}

AvlTree MakeEmpty(AvlTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, AvlTree T)
{
    if(T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Left);
    else if(X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

Position FindMin(AvlTree T)
{
    if (T == NULL)
        return NULL;
    while(T->Left)
        T = T->Left;
    return T;
}

Position FindMax(AvlTree T)
{
    if (T == NULL)
        return NULL;
    while(T->Right)
        T = T->Right;
    return T;
}

