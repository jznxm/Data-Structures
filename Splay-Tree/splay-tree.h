#include <stdlib.h>
#include "fatal.h"

typedef int ElementType;
#define Infinity 30000
#define NegInfinity (-30000)

struct SplayNode;
typedef struct SplayNode *SplayTree;

SplayTree MakeEmpty(SplayTree T);
SplayTree Find(ElementType X, SplayTree T);
SplayTree FindMin(SplayTree T);
SplayTree FindMax(SplayTree T);
SplayTree Initialize(void);
SplayTree Insert(ElementType X, SplayTree T);
SplayTree Remove(ElementType X, SplayTree T);
ElementType Retrieve(SplayTree T); /* Gets root item */
