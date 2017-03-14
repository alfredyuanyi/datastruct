struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue h);
void MakeEmpty(PriorityQueue h);
void Insert(ElementType x, PriorityQueue h);
ElementType DeleteMin(PriorityQueue h);
ElementType FindMin(PriorityQueue h);
int IsEmpty(PriorityQueue h);
int IsFull(PriorityQueue h);