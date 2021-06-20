#include <stdio.h>
#include "dlist.h"

int main()
{
    List L;
    Position tail;
    L = InitialList(NULL);
    printf("%d\n", IsEmpty(L));
    InsertAfter(5, L, Header(L));
    printf("%d\n", IsEmpty(L));
    InsertAfter(6, L, Header(L));
    InsertAfter(7, L, Tail(L));
    PrintList(L);
    PrintListBackwards(L);

    Delete(5, L);
    printf("%d\n", IsEmpty(L));
    PrintList(L);

    InsertAfter(9, L, Header(L));
    InsertAfter(12, L, Header(L));
    InsertAfter(16, L, Header(L));
    printf("%d\n", IsLast(FindPrevious(6, L), L));
    PrintList(L);
    PrintListBackwards(L);

    DeleteList(L);
    printf("结束。\n\n");

    return 0;
}