struct node;
typedef struct node* pToNode;
typedef pToNode doubleLinkedList;
typedef pToNode position;
typedef int elementType;

int IsEmpty(doubleLinkedList DL);
int IsLast(position p, doubleLinkedList DL);
int IsFirst(position p, doubleLinkedList DL);
position Find(elementType x, doubleLinkedList DL);
void Remove(elementType x, doubleLinkedList DL);
doubleLinkedList CreateDoubleLinkedList();
position NewNode();
position NewEmptyNode();
elementType InputElement();
void Insert(elementType frontNxodeValue, elementType x, doubleLinkedList DL);
void Replace(elementType before, elementType after, doubleLinkedList DL);
void Traverse(doubleLinkedList DL);
void DeleteList(doubleLinkedList DL);