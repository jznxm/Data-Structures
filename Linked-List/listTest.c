#include <stdio.h>
#include "fatal.h"
#include "list.h"

int main()
{
    List L;
    Position head, first;

    L = MakeEmpty(NULL);
    head = Header(L);
    printf("%d\n", IsEmpty(L));
    Insert(5, L, head);
    first = First(L);
    printf("第一个元素是: %d\n", first->Element);
    Insert(6, L, head);
    Insert(7, L, head);
    PrintList(head);

    Delete(5, L);
    printf("%d\n", IsEmpty(L));
    PrintList(L);

    Insert(9, L, head);
    Insert(12, L, head);
    Insert(16, L, head);
    printf("%d\n", IsLast(FindPrevious(6, L), L));
    PrintList(L);

    DeleteList(L);
    PrintList(L);
    printf("结束。\n\n");

    return 0;
}