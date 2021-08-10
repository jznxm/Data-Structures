#include <stdio.h>
#include "disjoint-set.h"

int main(void)
{
	DisjSet S;
	int i, j, k, Set1, Set2;

	Initialize(S);
	j = k = 1;
	while (k <= 8)
	{
		j = 1;
		while (j < NumSets)
		{
			Set1 = Find(j, S);
			Set2 = Find(j + k, S);
			SetUnion(S, Set1, Set2);
			j += 2 * k;
		}
		k *= 2;
	}
	i = 1;
	for (i = 1; i <= NumSets; i++)
	{
		Set1 = Find(i, S);
		printf("%d**", Set1);
	}
	printf("\n");

	return 0;
}