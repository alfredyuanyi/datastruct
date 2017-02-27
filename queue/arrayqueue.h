struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;

int IsFull(Queue q);
int IsEmpty(Queue q);
Queue CreateQueue(int queueSize);
void DisposeQueue(Queue q);
void MakeEmpty(Queue q);
ElementType Front(Queue q);
ElementType FrontAndDequeue(Queue q);
void Enqueue(ElementType x, Queue q);
void Dequeue(Queue q);