typedef struct Node
{
	int Element;
	struct Node *Prev;
	struct Node *Next;
} PtrToNode;

typedef PtrToNode *List;
typedef PtrToNode *Position;

List InitialList(List L);
void DeleteList(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(int X, List L);
Position FindPrevious(int X, List L);
void Delete(int X, List L);
void InsertAfter(int X, List L, Position P);
Position Header(List L);
Position Tail(List L);
Position Advance(Position P);
int Retrieve(Position P);
void PrintList(List L);
void PrintListBackwards(List L);
