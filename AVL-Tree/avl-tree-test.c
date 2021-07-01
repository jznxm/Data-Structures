#include <stdio.h>
#include "avl-tree.h"

int main(void)
{
    AvlTree T;
    Position P;
    int i, height;
    int j = 0;

    T = MakeEmpty(NULL);
    for (i = 0; i < 50; i++, j = (j + 7) % 50)
        T = Insert(j, T);
    for (i = 0; i < 50; i++)
        if ((P = Find(i, T)) == NULL || Retrieve(P) != i)
            printf("Error at %d\n", i);

    for (i = 0; i < 50; i += 2)
        T = Delete(i, T);

    for (i = 1; i < 50; i += 2)
        if ((P = Find(i, T)) == NULL || Retrieve(P) != i)
        {
            height = Height(P);
            printf("Height of tree: %d\n", height);
            printf("Error at %d\n", i);
        }

    printf("Min is %d, Max is %d\n", Retrieve(FindMin(T)),
           Retrieve(FindMax(T)));

    return 0;
}
