#include "heap.h"
#include "fatal.h"

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};

PriorityQueue Initialize(void)
{
	return NULL;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	if (H1->Element < H2->Element)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}

void SwapChildren(PriorityQueue H)
{
	PriorityQueue Tmp;

	Tmp = H->Left;
	H->Left = H->Right;
	H->Right = Tmp;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL) /* Single node */
		H1->Left = H2;	  /* H1->Right is already NULL,
                                       H1->Npl is already 0 */
	else
	{
		H1->Right = Merge(H1->Right, H2);
		if (H1->Left->Npl < H1->Right->Npl)
			SwapChildren(H1);

		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue SingleNode;

	SingleNode = malloc(sizeof(struct TreeNode));
	if (SingleNode == NULL)
		FatalError("Out of space!!!");
	else
	{
		SingleNode->Element = X;
		SingleNode->Npl = 0;
		SingleNode->Left = SingleNode->Right = NULL;
		H = Merge(SingleNode, H);
	}
	return H;
}

/* DeleteMin1 returns the new tree; */
/* To get the minimum, use FindMin */
/* This is for convenience */
PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap, RightHeap;

	if (IsEmpty(H))
	{
		Error("Priority queue is empty");
		return H;
	}

	LeftHeap = H->Left;
	RightHeap = H->Right;
	free(H);
	return Merge(LeftHeap, RightHeap);
}

ElementType FindMin(PriorityQueue H)
{
	if (!IsEmpty(H))
		return H->Element;
	Error("Priority Queue is Empty");
	return 0;
}

int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}
