#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct node
{
	int data;
	struct node *next;
}*basic = NULL, *newNode, *detectLoop = NULL;

typedef struct node N;

//Always past the list as double pointer, so that the reference is not lost
void Insert(N**,N*);
void Display(N*);
N* CreateNode(int);
bool DetectLoop(N*);

int main()
{
	int choice = 0;

	do
	{
		printf("\n1.Exit\n2.Insert\n3.Delete\n4.Display\n5.DetectLoop\nPlease enter your choice:");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				break;
			case 2:
				newNode = (N*)malloc(sizeof(N));
				printf("\n\nEnter the new element to be inserted(Only Integer):");
				scanf("%d", &newNode->data);
				newNode->next = NULL;
				Insert(&basic, newNode);
				break;

			case 3:
				break;

			case 4:
				printf("\nElements in the list are:");
				Display(basic);
				printf("\n");
				break;

			case 5:
				bool value;
				printf("\nCreating loop in the list");
				Insert(&detectLoop, CreateNode(20));
				Insert(&detectLoop, CreateNode(4));
				Insert(&detectLoop, CreateNode(15));
				Insert(&detectLoop, CreateNode(10));
				
				printf("\nList created:");
				Display(detectLoop);
				
				printf("\nSimulating Loop between 1st and Last.");
				detectLoop->next->next->next = detectLoop;

				printf("\nFinding the Loop...............");
				value = DetectLoop(detectLoop);

				if(value)
					printf("\nLOOP EXIST!");
				else
					printf("\nNO LOOP!");
				break;
		}
	}while(choice != 1);

	return 0;
}

/*This function is to create the node to be inserted into the list*/
N *CreateNode(int data)
{
	N *node = (N*)malloc(sizeof(N));
	node->data = data;
	node->next = NULL;

	return node;
}

/*The function is to inserted the given element into the given list*/
void Insert(N **root,N *toBeInserted)
{
	if(*root == NULL)
	{
		*root = toBeInserted;
	}
	else
	{
		N *iterator = *root;
		while(iterator->next != NULL)
			iterator = iterator->next;

		iterator->next = toBeInserted;
	}
}

/*This function is to display all the elements in the given list*/
void Display(N *start)
{
	N *iterator = start;
	if(iterator == NULL)
	{
		printf("List is empty!!!\n");
	}
	else
	{
		while(iterator != NULL)
		{
			printf("\t%d",iterator->data);
			iterator = iterator->next;
		}
	}
}

/*This function is to find the loop in the given list*/
bool DetectLoop(N *list)
{
	bool returnValue = false;

	N *slowIterator = list, *fastIterator = list;
	while(slowIterator && fastIterator && fastIterator->next)
	{
		slowIterator = slowIterator->next;
		fastIterator = fastIterator->next->next;

		if(slowIterator == fastIterator)
		{
			returnValue = true;
			break;
		}
	}

	return returnValue;
}
