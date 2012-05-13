#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "diff.h"


void insert(int count, unsigned long data,struct hash_vec ** head,struct hash_vec **end)
{
	struct hash_vec *temp=NULL;
	
	if(*head==NULL)
	{
		temp = (struct hash_vec *)malloc(sizeof(struct hash_vec));
		temp->next=NULL;
		temp->lno = count;
	
		temp->hash = data;
		*head = *end = temp;
	}
	else 
	{
		temp = (struct hash_vec *)malloc(sizeof(struct hash_vec));
		temp->next=NULL;
		temp->lno = count;
			
		temp->hash = data;
		
		(*end)->next = temp;
		*end = temp;
	//	end->next=NULL;
	
	}
}

int adjustll(struct hash_vec *head)
{
	int size=0;
	
	
	struct hash_vec *p;
	p = head;
	while((p->next)!=NULL)
	{
		++size;
		p = p->next;
	}
	p->next=NULL;
	return size+1;
	
}

void printll(struct hash_vec *head)
{
	
	printf("\nFILE------\n");
//	adjustll(head);
	struct hash_vec *p;
	p = head;
	while(p!=NULL)
	{
		printf("line : %d  hash : %lu\n",p->lno,p->hash);
		p = p->next;
	}
	
	
}
void sort(struct hash_vec *head)
{
	
	
	struct hash_vec *p1,*p2;
	int temps;
	unsigned long templ;
	p1=p2=NULL;
	p1 = head;
	while(p1->next!=NULL)
	{
		p2 = head;
		while(p2->next!=NULL)
		{
			if((p2->hash)>(p2->next->hash))
			{
				temps = p2->lno;
				templ = p2->hash;
				p2->lno = p2->next->lno;
				p2->hash = p2->next->hash;
				p2->next->lno = temps;
				p2->next->hash = templ;
			}
			
			else if ((p2->hash)==(p2->next->hash))
			{
				
				if((p2->lno)>(p2->next->lno))
				{
					
					temps = p2->lno;
					templ = p2->hash;
					p2->lno = p2->next->lno;
					p2->hash = p2->next->hash;
					p2->next->lno = temps;
					p2->next->hash = templ;
					
				}				
				
			}
		
			p2=p2->next;
		
		}
		p1=p1->next;
	}
	
	
	
	
}



int gete(struct hash_vec * start,struct equiclass *arr)
{

//	struct equiclass *ehead,*eend,*etemp;
//	ehead = etemp = eend = NULL;
	struct equiclass etemp;
	int counter = 1;
	int realc = 0;
	arr[0].lno=0;
	arr[0].last=1;
	while(start!=NULL)
	{
	
		
		etemp.lno = start->lno;
		if((start->next==NULL) ||(start->hash != start->next->hash))
		{
			etemp.last = 1; // 1 stands for true
		}
		else
			etemp.last=0;
		
	/*	if(ehead==NULL)
		{
			ehead=eend=etemp;
		}
		else
		{
			eend->next=etemp;
			eend=etemp;
		}*/
			
			arr[counter++] = etemp;
	
		start=start->next;	
	
		
	}
	
	return counter;	
}

void printel(struct equiclass *p,int count)
{
	
	/*while(p!=NULL)
	{
		printf("line : %d  last : %d\n",p->lno,p->last);
		p = p->next;
	}*/
		int i=0;
	for(i;i<count;i++)
	{
		printf("line : %d  last : %d\n",p[i].lno,p[i].last);	
	}
	
}

void getarray(struct hash_vec *head , struct hash_vec *arr)
{
	int counter = 0;
	while(head!=NULL)
	{
		arr[++counter].lno = head->lno;
		arr[counter].hash = head->hash;
		head=head->next;
	}	
	
	
}
void printarray(struct hash_vec *arr,int size)
{
	
	int i=1;
	for(i;i<=size;i++)
	{
		printf("\n lno = %d   hash = %lu",arr[i].lno,arr[i].hash);
	}
	
}


void fillp(int *p , struct equiclass *ehead , struct hash_vec *file1,struct hash_vec *file2,int last,int size)
{
	
	int beg,mid,end,i,loc;
	
	for(i=1;i<=size+1;i++)
	{
		beg=1;
		end = last;
		loc=0;
	
		while(beg<=end)
		{
					mid = (int)(beg+end)/2;
		//	printf("\nWTF beg:%d  end:%d  mid: %d\n",beg,end,mid);
	
			if((file1[i].hash == file2[mid].hash) && (ehead[mid-1].last==1))
			{
				loc = mid;
				break;
			}
			else if((file1[i].hash == file2[mid].hash))
			{
				int j = mid;
				while(ehead[j-1].last!=1)
					j--;
				loc = j;
				break;
				
			}
			
			else if((file1[i].hash < file2[mid].hash))
			{
				
				end = mid-1;
			}
			else
				beg = mid+1;
			
		}
		
		p[i] = loc;	
	}
	
	

	for(i=1;i<=size;i++)
	{
		printf(" %d\n",p[i]);
	}

}




void diff(char *name1,char *name2) 
{
	FILE *fp;
	char buff[1024];
	int count=0,flag=0,ecount=0,sz2=0,sz1=0; // stores the number of lines
	struct hash_vec *head1,*head2 ,*end1,*end2,*file1,*file2;
	struct equiclass *ehead=NULL;
	head1=end1=head2=end2=NULL;
	unsigned long aux =0;
	if((fp=fopen(name1,"r"))!=NULL)
	{
		flag=1;
		while(!feof(fp))
		{
			int i;
			aux=0;
			fgets(buff,1024,fp);
			count++;
		//	printf("\n count-%d - %s ",count,buff);
			for(i=0;i<strlen(buff);i++)
			{
				aux  = aux + i*(int)buff[i];
				
			}
			insert(count,aux,&head1,&end1);
		
			
		}
	
		fclose(fp);		
	}
	
 	else
	{
		printf("\n ERROR: file %s couldnt be opened",name1);
	}
	
	count=0;
		
	if((fp=fopen(name2,"r"))!=NULL)
	{
		flag=1;
		while(!feof(fp))
		{
			int i;
			aux=0;
			fgets(buff,1024,fp);
			count++;
		//	printf("\n count-%d - %s ",count,buff);
			for(i=0;i<strlen(buff);i++)
			{
				aux  = aux + i*(int)buff[i];
				
			}
			insert(count,aux,&head2,&end2);
		
			
		}
	
		fclose(fp);		
	}
	
 	else
	{
		printf("\n ERROR: file %s couldnt be opened",name2);
	}

sz1=adjustll(head1);
sz2=adjustll(head2);
printf("\n size1 : %d    size2 : %d  \n",sz1,sz2);
	
	sort(head2);
	printll(head2);
	ehead = malloc(sz2*sizeof(struct equiclass));
	ecount=gete(head2,ehead);
	printel(ehead,ecount);

file1 = malloc(sz1*sizeof(struct hash_vec));
file2 = malloc(sz2*sizeof(struct hash_vec));
getarray(head1,file1);
getarray(head2,file2);
//	printll(head1);
//	printll(head2);
//	printf("\n now arrays\n");
//	printarray(file1,sz1);
//	printarray(file2,sz2);

int p[sz1];
fillp(p,ehead,file1,file2,sz2,sz1);	// because array starts from 1

}








