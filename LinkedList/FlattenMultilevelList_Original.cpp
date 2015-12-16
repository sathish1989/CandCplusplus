#include<iostream>
#include<stdlib.h>

using namespace std;

/*Macro to find the size of the array*/
#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

struct node
{
	int data;
	struct node *next;
	struct node *child;
}; //DONOT FORGOT TO INCLUDE (;)

typedef struct node N;

N *CreateList();
void FlattenList(N*);
void PrintList(N*);
N *CreateSubList(int*,int); //ALWAYS IF ARRAY IS PASSED, THEN POINTER IS RECEIVED IN THE PARAMETER AND NOT THE WHOLE ARRAY. Eg. int* not as int[]

/*Function to remove child and store it as a single list. Fattening level by level*/
void FlattenList(N *root)
{
	N *head, *tail, *curr, *tmp;

	if(root == NULL)
		return;

	//Storing the beginning node as head
	head = root;

	while(root->next)
		root = root->next;

	//Storing the last node as current tail
	tail = root;

	//Process each node in the list from level 1.
	curr = head;
	while(curr != tail)
	{
		//if the node has a child
		if(curr->child)
		{
			//make child as tail of previous level
			tail->next = curr->child;

			//make the child's tail and my parent's new tail
			tmp = curr->child;
			while(tmp->next)
				tmp = tmp->next;

			tail = tmp;
		}
		
		curr = curr->next;
	}
}

void PrintList(N *head)
{
	if(head == NULL)
		return;

	cout<<"\nThe flattened list elements are ";
	while(head != NULL)
	{
		cout<<"\t"<<head->data;
		head = head->next;
	}
	cout<<endl;
}

/*Function to create the list Array of integers*/
N *CreateSubList(int *arr, int count)
{
	N *head = NULL;
	N *p;

	for(int i=0; i<count; ++i)
	{
		if(head == NULL)
		{
			head = (N*)malloc(sizeof(N));
			p = head;
		}
		else
		{
			//PLEASE USE YOUR HEAD. HOW CAN WE DECLARED P IF ITS ALREADY DECLARED. p = (N*)malloc(sizeof(N));
			p->next = (N*)malloc(sizeof(N));
			p = p->next;
		}

		p->data = arr[i];
		p->next = NULL;
		p->child = NULL;
	}

	return head;
}

/*Function to create the multilevel list*/
N *CreateList()
{
	int arr1[] = {10, 5, 12, 7, 11};
    	int arr2[] = {4, 20, 13};
    	int arr3[] = {17, 6};
    	int arr4[] = {9, 8};
    	int arr5[] = {19, 15};
    	int arr6[] = {2};
    	int arr7[] = {16};
    	int arr8[] = {3};

	N *head1 = CreateSubList(arr1,SIZE(arr1));
	N *head2 = CreateSubList(arr2,SIZE(arr2));
	N *head3 = CreateSubList(arr3,SIZE(arr3));
	N *head4 = CreateSubList(arr4,SIZE(arr4));
	N *head5 = CreateSubList(arr5,SIZE(arr5));
	N *head6 = CreateSubList(arr6,SIZE(arr6));
	N *head7 = CreateSubList(arr7,SIZE(arr7));
	N *head8 = CreateSubList(arr8,SIZE(arr8));

	head1->child = head2;
	head1->next->next->next->child = head3;
    	head3->child = head4;
    	head4->child = head5;
    	head2->next->child = head6;
    	head2->next->next->child = head7;
    	head7->child = head8;

	return head1;
}

int main()
{
	N *head = NULL;
	head = CreateList();
	FlattenList(head);
	PrintList(head);
	
	return 0;
}

