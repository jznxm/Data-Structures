#include "fatal.h"
#include "heap.h"

#define MaxSize (1000)

int main(void)
{
	PriorityQueue H;
	int i, j;

	H = Initialize(MaxSize);
	for (i = 0, j = MaxSize / 2; i < MaxSize; i++, j = (j + 71) % MaxSize)
		Insert(j, H);

	j = 0;
	while (!IsEmpty(H))
		if (DeleteMin(H) != j++)
			printf("Error in DeleteMin, %d\n", j);
	printf("Done...\n");
	return 0;
}