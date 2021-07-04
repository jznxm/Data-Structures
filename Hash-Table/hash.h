#define MinTableSize (10)

typedef int ElementType;
typedef unsigned int Index;

typedef struct Node
{
	ElementType Element;
	struct Node *Next;
} ListNode;

typedef ListNode *Position;
typedef Position List;

/* though this wastes space */
struct HashTbl
{
	int TableSize;
	List *TheLists;
};

typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void MakeEmpty(HashTable H);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
Position FindPrevious(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
void Delete(ElementType Key, HashTable H);
ElementType Retrieve(Position P);