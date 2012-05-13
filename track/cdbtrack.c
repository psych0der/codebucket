#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdbtrack.h"


int filecheck(void)
{
	FILE *fp;
	fp=fopen("./.cdb/cdb.track","r");
	if(fp==NULL)
	{
		printf("\n TRACKING not initiated\n");
		fclose(fp);
		return 0;
	}
	else
	{
		printf("\n TRACKING intact\n");
		fclose(fp);
		return 1;
	}
	
}

int createtrack(void)
{

	FILE *fp;
	if((fp=fopen("./.cdb/cdb.track","wb"))!=NULL)
	{
     	fclose(fp);	
		return 1;
	}
	
	
}

int writetrack(void)
{
	
	FILE *fp;
	if((fp=fopen("./.cdb/cdb.track","a+b"))!=NULL)
	{
     	if(ftell(fp)==0)
			{
				printf("empty file\n");
			//	fprintf(fp,"%d\n",0);
			//	printf("updated\n");
				fclose(fp);
				return 0;
			}
	}
	else
	{
		printf("lol\n");
	}
	
	
}

int readcontents(void)
{
	FILE *fp;
	struct trackst t;
	int n=0;
	if((fp=fopen("./.cdb/cdb.track","rb"))!=NULL)
	{
		
		if(feof(fp))
		{
			fclose(fp);
			return n;	
			
		}
		else
		{
			while(!feof(fp))
			{
				fread(&t,sizeof(t),1,fp);
				n++;
				
			}
			
		}
		
		fclose(fp);
		return n;
		
	}
	else
	{
		return -1;
	}
	
	
}

int addfile(struct trackst *p)
{
	printf("name to be updated : %s\n",p->name);
	FILE *fp;
	struct trackst f;
	int avail=0;
	fp =fopen("./.cdb/cdb.track","rb");
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			fread(&f,sizeof(struct trackst),1,fp);
		
			if(!strcmp(p->name,f.name))
			{
				printf("\n???\n");
				avail =1;
			}
		}
	
		fclose(fp);
		if(avail)
		{
			printf("File already tracked\n");
			return -1;
		}
		
		else
		{
			
		if((fp = fopen("./.cdb/cdb.track","a+b"))!=NULL)
		{
			fwrite(p,sizeof(struct trackst),1,fp);
			fclose(fp);
			return 1;
			
		}
		else
		{
			printf("\n error updating tracking list");
			return -1;
		}	
		
		}
		
	}	
	
}
void printtl()
{
	
	FILE *fp;
	struct trackst f;
	fp =fopen("./.cdb/cdb.track","rb");
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			fread(&f,sizeof(struct trackst),1,fp);
			printf("------\n");
			printf("name : %s  \nctime : %ld\nmtime : %ld\n checksum : %lu\n",f.name,f.ctime,f.mtime,f.checksum);
	 	}
	}
	else
	{
		printf("Error:unable to print tracking list\n");
		exit(1);
	}
	
}