struct StackRecord;
typedef struct StackRecord *Stack;
typedef int ElementType;

int IsEmpty(Stack s);
int IsFull(Stack s);
Stack CreateStack(int maxElements);
void DisposeStack(Stack s);
void MakeEmpty(Stack s);
void Push(ElementType x, Stack s);
ElementType Top(Stack s);
void Pop(Stack s);
ElementType TopAndPop(Stack s);
