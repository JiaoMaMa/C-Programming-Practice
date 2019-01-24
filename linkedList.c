#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node* next;
} node;

//helper function to create a new node with a given value
node* createNode(int value)
{
	node* newNode = (node*) malloc(sizeof(node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

//insert an element into the linkedList
void insert(node** startPtr, int value)
{
	if (*startPtr == NULL)
	{
		*startPtr = createNode(value);
	}
	else
	{
		insert(&(*startPtr)->next,value);
	}
}

//search the index of an element in the linkedList
//return -1 if not found, return the index if found
int searchIndex(node* start,int value)
{
	int count = 0;
	while (start!=NULL)
	{
		if (start->value == value)
		{	
			return count;
		}
		else
		{
			start=start->next;
			count++;
		}
	}
	return -1;
}

//delete an element from the linkedList (with order unchanged)
//does nothing if not found
void delete(node** startPtr, int value)
{
	if (searchIndex(*startPtr,value) == -1)
	{
		return;
	}
	else if ((*startPtr)->value == value)
	{
		node* temp = (*startPtr)->next;
		free(*startPtr);
		*startPtr = temp;
	}
	else
	{
		delete(&(*startPtr)->next,value);
	}
}

//concatenate two linkedLists
//returns a pointer to the newList
node* concatonate(node* list1, node* list2)
{
	while (list2 != NULL)
	{
		insert(&list1,list2->value);
		list2 = list2->next;
	}
	return list1;
}

//print all the elements in the list
void printList(node* start)
{
	if (start!=NULL)
	{
		printf("%d ",start->value);
		printList(start->next);
	}
}

//free the list
void freeList(node** startPtr)
{
	free(*startPtr);
	*startPtr = NULL;
}

int main()
{
	printf("------Test------\n");
	node* start = NULL;
	printf("Insert elements 15,8,20,16,21 into tree1 respectively:\n");
	insert(&start,15);
	insert(&start,8);
	insert(&start,20);
	insert(&start,16);
	insert(&start,21);
	printf("list1:\n");
	printf("Expected: 15 8 20 16 21 \n");
	printf("Actual: ");
	printList(start);
	printf("\n");

	printf("\n");
	printf("Display the index of each element in list1: \n");
	printf("Expected: 0 1 2 3 4 \n");
	printf("Actual: ");
	printf("%d ",searchIndex(start,15));
	printf("%d ",searchIndex(start,8));
	printf("%d ",searchIndex(start,20));
	printf("%d ",searchIndex(start,16));
	printf("%d ",searchIndex(start,21));
	printf("\n");
	
	printf("\n");
	printf("Display the index of 17 in list1: \n");
	printf("Expected: -1 \n");
	printf("Actual: ");
	printf("%d ",searchIndex(start,17));
	printf("\n");

	printf("\n");
	printf("Delete element 20 from list1: \n");
	delete(&start,20);
	printf("list1:\n");
	printf("Expected: 15 8 16 21 \n");
	printf("Actual: ");
	printList(start);
	printf("\n");
	
	printf("\n");
	printf("Delete element 9 from list1: \n");
	delete(&start,9);
	printf("list1:\n");
	printf("Expected: 15 8 16 21 \n");
	printf("Actual: ");
	printList(start);
	printf("\n");
	
	printf("\n");
	printf("Display the index of each element in list1: \n");
	printf("Expected: 0 1 2 3 \n");
	printf("Actual: ");
	printf("%d ",searchIndex(start,15));
	printf("%d ",searchIndex(start,8));
	printf("%d ",searchIndex(start,16));
	printf("%d ",searchIndex(start,21));
	printf("\n");
	
	printf("\n");
	printf("Display the index of 20 in list1: \n");
	printf("Expected: -1 \n");
	printf("Actual: ");
	printf("%d ",searchIndex(start,20));
	printf("\n");

	node* start2 = NULL;
	printf("\n");
	printf("Insert elements 10,4,19 into list2 respectively:\n");
	insert(&start2,10);
	insert(&start2,4);
	insert(&start2,19);
	printf("list2:\n");
	printf("Expected: 10 4 19 \n");
	printf("Actual: ");
	printList(start2);
	printf("\n");

	printf("\n");
	printf("Concatonate list 1 and list 2: \n");
	node* newList= concatonate(start,start2);
	printf("new List:\n");
	printf("Expected: 15 8 16 21 10 4 19 \n");
	printf("Actual: ");
	printList(newList);
	printf("\n");
	
	printf("\n");
	printf("Free the new list: \n");
	freeList(&newList);
	printf("new List:\n");
	printf("Expected: \n");
	printf("Actual: ");
	printList(newList);
	printf("\n");
	printf("------Test Finished------\n");
	
}