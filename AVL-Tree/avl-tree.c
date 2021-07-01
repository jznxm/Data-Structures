#include "fatal.h"
#include "avl-tree.h"

struct AvlNode
{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

int Max(int left, int right)
{
    return left > right?  left : right;
}

int Height(Position P)
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

static Position SingleRotateWithLeft(Position K2)
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1;
    
    return K1;
}

static Position SingleRotateWithRight(Position K2)
{
    Position K1;

    K1 = K2->Right;
    K2->Right = K1->Left;
    K1->Left = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Right), K2->Height) + 1;
    
    return K1;
}


static Position DoubleRotateWithLeft(Position K3)
{
    /* rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight(K3->Left);

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight(Position K3)
{
    /* rotate between K1 and K2 */
    K3->Right = SingleRotateWithLeft(K3->Right);

    /* Rotate between K3 and K2 */
    return SingleRotateWithRight(K3);
}

AvlTree Insert(ElementType X, AvlTree T)
{
    if (T == NULL)
    {
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        if(T == NULL)
            FatalError("Out of space!!!");
        else
        {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if(X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else    
                T = DoubleRotateWithLeft(T);
        }
    }
    else if(X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (X < T->Left->Element)
                T = SingleRotateWithRight(T);
            else    
                T = DoubleRotateWithRight(T);
        }
    }

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

AvlTree Delete(ElementType X, AvlTree T)
{
    Position TmpCell;    

    if (T == NULL)
    {
        Error("Element not found");
    }
    else if (X < T->Element) 
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right)
    {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else
    {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }

    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}
