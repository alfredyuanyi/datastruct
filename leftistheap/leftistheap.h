struct TreeNode;
typedef struct TreeNode *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(void);
ElementType FindeMin(PriorityQueue h);
int IsEmpty(PriorityQueue h);
PriorityQueue Merge(PriorityQueue h1, PriorityQueue h2);

/* 为了使左式堆的Insert与二叉堆的Insert兼容,使用此宏定义 */
#define Insert(x, h) (h = Insert1((x), h));

PriorityQueue Insert1(ElementType x, PriorityQueue h);
PriorityQueue DeleteMin(PriorityQueue h);

