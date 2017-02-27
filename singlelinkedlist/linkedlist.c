#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

//define the node of linkedlist.
struct node
{
	elementType element;
	position next;
}Node;
// input an element of node and return the element value inputed.
elementType InputElement()
{
	elementType a;
	printf("please input an element:");
	scanf("%d", &a);
	return a;
}
//input an element to create a new nod and return it's pointer.
position NewNode()
{
	position p;
	p = malloc( sizeof( Node ) );
	if( p == NULL )
	{
		printf("Out of space!");
		exit(1);
	}
	p->next = NULL;
	p->element = InputElement();
	return p;
}
// create a new linkedlist and return it's first pointer.
// notice: this function create a new linkedList which does not have a header pointer.
linkedList CreateLinkedList()
{
	position first = NULL, currentNode = NULL, newNode;
	char c;
	while(tolower(c) != 'n')
	{
		newNode = NewNode();
		if(first != NULL) currentNode->next = newNode; 
		else first = newNode;
		currentNode = newNode;
		printf("do you want input annother element? y/n  ");
		while((c = getchar()) == '\n') ;
	}
	return first;
}

int IsEmpty(linkedList L)
{
	return L == NULL;
}

int IsLast(position P, linkedList L)
{
	return P->next == NULL;
}
position Find(elementType X, linkedList L)
{
	position p = L;
	while(p != NULL && p->element != X)
	{
		p = p->next;
	}
	return p;
}
position FindPrevious(elementType X, linkedList L)
{
	position p = L;
	while(p != NULL && p->next->element != X)
	{
		p = p->next;
	}
	return p;
}
void Delete(elementType X, linkedList L)
{
	position P, temp = NULL;
	P = FindPrevious(X, L);
	if( !IsLast(P, L) )
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

}
void Insert(elementType X, linkedList L, position P)
{
	position temp;
	temp = malloc( sizeof(Node));
	if( temp == NULL )
	{
		printf("Out of space!");
	}
	temp->element = X;
	temp->next = P->next;
	P->next = temp;
}
void DeleteList(linkedList L)
{
	position p, temp;
	p = L->next;
	L->next = NULL;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}
void Traverse(linkedList L)
{
	position p;
	p = L;
	while(p != NULL)
	{
		printf("p->element = %d \n", p->element);
		p = p->next;
	}
}
int main()
{
	linkedList L;
	L = CreateLinkedList();
	Traverse(L);
	position p = Find(1, L);
	if(!p) printf("didn't find any node.element = 1!\n");
	else printf("find node.element = %d\n", p->element);
	Delete(1, L);
	p = Find(1, L);
	if(!p) printf("didn't find any node.element = 1!\n");
	else printf("find node.element = %d\n", p->element);
	p = Find(3, L);
	Insert(1, L, p);
	Traverse(L);
	DeleteList(L);
	Traverse(L);
	printf("programe excuted succeed!\n");
	return 0;
}
