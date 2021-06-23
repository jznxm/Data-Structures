#include "fatal.h"

#define MaxDegree 100

static int
Max(int A, int B)
{
    return A > B ? A : B;
}

typedef struct
{
    int CoeffArray[MaxDegree + 1];
    int HighPower;
} * Polynomial;

void ZeroPolynomial(Polynomial Poly)
{
    int i;

    for (i = 0; i <= MaxDegree; i++)
        Poly->CoeffArray[i] = 0;
    Poly->HighPower = 0;
}

void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2,
                   Polynomial PolySum)
{
    int i;

    ZeroPolynomial(PolySum);
    PolySum->HighPower = Max(Poly1->HighPower,
                             Poly2->HighPower);

    for (i = PolySum->HighPower; i >= 0; i--)
        PolySum->CoeffArray[i] = Poly1->CoeffArray[i] + Poly2->CoeffArray[i];
}

void MultPolynomial(const Polynomial Poly1,
                    const Polynomial Poly2, Polynomial PolyProd)
{
    int i, j;

    ZeroPolynomial(PolyProd);
    PolyProd->HighPower = Poly1->HighPower + Poly2->HighPower;

    if (PolyProd->HighPower > MaxDegree)
        Error("Exceeded array size");
    else
        for (i = 0; i <= Poly1->HighPower; i++)
            for (j = 0; j <= Poly2->HighPower; j++)
                PolyProd->CoeffArray[i + j] +=
                    Poly1->CoeffArray[i] *
                    Poly2->CoeffArray[j];
}

#if 0
        typedef struct Node *PtrToNode;

        struct Node
        {
            int Coefficient;
            int Exponent;
            PtrToNode Next;
        };

        typedef PtrToNode Polynomial;  /* Nodes sorted by exponent */
#endif

void PrintPoly(const Polynomial Q)
{
    int i;

    for (i = Q->HighPower; i > 0; i--)
        printf("%dx^%d + ", Q->CoeffArray[i], i);
    printf("%d\n", Q->CoeffArray[0]);
}

int main()
{
    Polynomial P, Q;

    P = (Polynomial)malloc(sizeof(*P));
    Q = (Polynomial)malloc(sizeof(*Q));

    P->HighPower = 1;
    P->CoeffArray[0] = 1;
    P->CoeffArray[1] = 1;
    MultPolynomial(P, P, Q);
    MultPolynomial(Q, Q, P);
    AddPolynomial(P, P, Q);
    PrintPoly(Q);

    return 0;
}
