#include <stdio.h>
#include<conio.h>
#include <malloc.h>

struct link
{
	int data;
	unsigned long info;
	struct  link *next;
};

int i;
int number ;
struct   link *start, *node,*n, *previous, *new1, *counter;

void doubly_link_sort()
{
	printf("\n Input the number of node we need to create: ");
	scanf("%d", &number );

	start->next = NULL;

	node = start;

	/* CREATE A LINKED LIST */

	for (i = 0; i < number ; i++)
	{
		node->next = (struct link* ) malloc(sizeof(struct link));
		node = node->next;
		printf("\n Input the first node: %d: ", i+1);
		scanf("%d", &node->data);
		scanf("%ul",&node->info);
		node->next = NULL;
	}

	/* END OF CREATION   */

	/* SORTING THE LINK LIST START FROM HERE */

	new1 = start;
	for(; new1->next != NULL; new1 = new1->next)
	{
		for(counter = new1->next; counter != NULL; counter = counter->next)
		{
			if(new1->data >= counter->data)
			{
				int temp = new1->data;
				unsigned long t=new1->info;
				new1->data = counter->data;
				new1->info=counter->info;
				counter->data = temp;
				counter->info=t;
			}
		}
	}

	/* END OF SORTING */

	/* Display the list */

	node = start->next;
	printf("\n After sorting the list is as follows:\n");
	printf(" data(int)\t");
	while (node)
	{
		printf(" %d", node->data);
		node = node->next;
	}
	n=start->next;
	printf("\n nfo(unsigned)\t");
	while (n)
	{
		printf(" %d", n->info);
		n = n->next;
	}
}

void main()
{       clrscr();
	doubly_link_sort();
	getch();
}