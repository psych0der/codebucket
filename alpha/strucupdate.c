#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Emp
{
	
	char name[20];
	int age;
	int sal;
	
	
};

int main()
{
	FILE *fp;
	fp = fopen("sample.rb","wb");
	struct Emp emp;
	char nam[20];
	int i;
	for(i=0;i<5;i++)
	{
		
		printf("\nname ? ");
		scanf("%s",emp.name);
		printf("\nage ? ");
		scanf("%d",&emp.age);
		printf("\nsal ? ");
		scanf("%d",&emp.sal);
		fwrite(&emp,sizeof(struct Emp),1,fp);
		
	}
	fclose(fp);
	printf("\n enter the name to be updated\n");
		scanf("%s",nam);
	fp = fopen("sample.rb","r+b");
	while(fread(&emp,sizeof(struct Emp),1,fp))
	{
		
		if(!strcmp(nam,emp.name))
		{
			printf("\n enter new name ");
			scanf("%s",nam);
			strcpy(emp.name,nam);
			fseek(fp,-sizeof(struct Emp),SEEK_CUR);
			fwrite(&emp,sizeof(struct Emp),1,fp);
			break;
		}
		
	}
	fclose(fp);
	fp = fopen("sample.rb","rb");
	while(fread(&emp,sizeof(struct Emp),1,fp))
	{
		
		printf("\n name : %s     age : %d   salary :%d\n",emp.name,emp.age,emp.sal);
		
	}
	
	
	
	
}