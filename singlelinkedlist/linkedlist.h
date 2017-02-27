struct node;
typedef struct node* preToNode;
typedef preToNode linkedList;
typedef preToNode position;
typedef int elementType;

linkedList MakeEmpty(linkedList L);
int IsEmpty(linkedList L);
int IsLast(position P, linkedList L);
position Find(elementType X, linkedList L);
void Delete(elementType X, linkedList L);
position FindPrevious(elementType X, linkedList L);
void Insert(elementType X, linkedList L, position P);
void DeleteList(linkedList L);
position Header(linkedList L);
position First(linkedList L);
elementType Retrieve(position P);
elementType InputElement();
position NewNode();
linkedList CreateLinkedList();
void Traverse(linkedList L);



