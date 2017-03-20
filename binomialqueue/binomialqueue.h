struct BinNode;
struct Collection;
typedef struct BinNode *Position;
typedef struct BinNode *BinTree;
typedef struct Collection *BinQueue;
typedef int ElementType;

BinQueue Initialize(void);
int IsEmpty(BinQueue h);
ElementType FindMin(BinQueue h);
BinQueue Merge(BinQueue h1, BinQueue h2);
BinQueue Insert(ElementType x, BinQueue h);
ElementType DeleteMin(BinQueue h);