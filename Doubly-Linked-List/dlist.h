#ifndef _LIST_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
void DeleteList(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(int X, List L);
Position FindPrevious(int X, List L);
void Delete(int X, List L);
void Insert(int X, List L, Position P);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
int Retrieve(Position P);

void PrintList(List L);

#endif