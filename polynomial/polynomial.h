struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Polynomial;
typedef int elementType;

PtrToNode NewNode();
PtrToNode NewEmptyNode();
Polynomial NewPolynomial();
void Traverse(Polynomial p);
void AddPolynomial(const Polynomial p1,
                const Polynomial p2,
                Polynomial p);
void MultPolynomial(const Polynomial p1,
                const Polynomial p2,
                Polynomial p);

