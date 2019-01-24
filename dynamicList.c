#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 10; //initial capacity of the dynamic sized array

typedef struct list
{
	int used;
	int size;
	int* array;
} list;

//initialize a list with INITIAL_CAPACITY
void initList(list* start)
{
	start->used = 0;
	start->size = INITIAL_CAPACITY;
	start->array = (int*) malloc(start->size * sizeof(int));
}

//insert an element into the array
//reallocate memory if necessary
void insert(list* start, int value)
{
	if (start->used == start->size) 
	{
    	start->size *= 2;
    	start->array = (int*)realloc(start->array, start->size * sizeof(int));
  	}
 	start->array[start->used++] = value;
}

//search the index of an element in the list
//returns -1 if not found, returns the index if found
int searchIndex(list* start, int value)
{
	for (int i = 0; i < start->used; i++)
	{
		if (value == start->array[i])
		{
			return i;
		}
	}
	return -1;
}

//helper function to shift the rest of the array starting from idx one place left
void moveArray(list* start, int idx)
{
	for (int i = idx; i<start->used; i++)
	{
		start->array[i] = start->array[i+1];
	}
}

//delete an element in the array with the order unchanged (if found)
//does nothing if not found
void delete(list* start, int value)
{
	int idx = searchIndex(start,value);
	if (idx == -1)
	{
		return;
	}
	else
	{
		start->used--;
		moveArray(start,idx);
	}
}

//print the list of elements
void printList(list* start)
{
	for (int i = 0; i< start->used; i++)
	{
		printf("%d ", start->array[i]);
	}
}

//free the list
void freeList(list* start) 
{
  free(start->array);
  start->array = NULL;
  start->used = start->size = 0;
}

int main()
{
	printf("------Test------\n");
	printf("Insert elements 1-10 into list respectively:\n");
	list start;
	initList(&start);
	for (int i = 0; i< 10; i++)
	{
		insert(&start,i+1);
	}
	printf("Expected: 1 2 3 4 5 6 7 8 9 10 \n");
	printf("Actual: ");
	printList(&start);
	printf("\n");
	
	printf("\n");
	printf("Print the index of each element: \n");
	printf("Expected: 0 1 2 3 4 5 6 7 8 9 \n");
	printf("Actual: ");
	for (int i = 0; i< 10; i++)
	{
		printf("%d ",searchIndex(&start,i+1));
	}
	printf("\n");
	
	printf("\n");
	printf("Insert 11 into the list: \n");
	printf("Expected: 1 2 3 4 5 6 7 8 9 10 11 \n");
	printf("Actual: ");
	insert(&start,11);
	printList(&start);
	printf("\n");
	
	printf("\n");
	printf("Delete 8 from the list: \n");
	printf("Expected: 1 2 3 4 5 6 7 9 10 11 \n");
	printf("Actual: ");
	delete(&start,8);
	printList(&start);
	printf("\n");
	
	printf("\n");
	printf("Delete 11 from the list: \n");
	printf("Expected: 1 2 3 4 5 6 7 9 10 \n");
	printf("Actual: ");
	delete(&start,11);
	printList(&start);
	printf("\n");
	
	printf("\n");
	printf("Delete 26 from the list: \n");
	printf("Expected: 1 2 3 4 5 6 7 9 10 \n");
	printf("Actual: ");
	delete(&start,26);
	printList(&start);
	printf("\n");
	
	printf("\n");
	printf("Free the list: \n");
	printf("Expected: \n");
	printf("Actual: ");
	freeList(&start);
	printList(&start);
	printf("\n");
	printf("------Test Finished------\n");
}