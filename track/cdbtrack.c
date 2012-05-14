#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdbtrack.h"


int filecheck(void)
{
	FILE *fp;
	fp=fopen("./.cdb/cdb.track","rb");
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
			while(fread(&t,sizeof(t),1,fp))
			{
				
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



struct trackst * search(char *namerequest)
{
	struct trackst *f,g;
	f = (struct trackst *)malloc(sizeof(struct trackst ));
	
	FILE *fp;
	if((fp=fopen("./.cdb/cdb.track","rb"))!=NULL)
	{
		
	//	fread(f,sizeof(struct trackst),1,fp);
	//	rewind(fp);
			//while(fread(f,sizeof(struct trackst),1,fp))
		while(!feof(fp))
		{
	
		fread(f,sizeof(struct trackst),1,fp);
			if(!strcmp(namerequest,f->name))
			{
				g=*f;
				return f;
			}
		
	 	}
		fclose(fp);
		return NULL;
		
	}
	else
	{
		printf("Error:unable access tracking list\n");
	}
	
	
	
	
}





int addfile(struct trackst *p)
{
	printf("FILE to be tracked : %s\n",p->name);
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
			//	printf("\n???\n");
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

	fp =fopen("./.cdb/cdb.track","a+b");
	if(fp!=NULL)
	{
		//	printf("\nkyon?\n");
		if(ftell(fp)==0)
		{
		
			printf("\n tracking list empty\n");
			fclose(fp);
			exit(1);
		}
		
	else
	{
		fclose(fp);
			fp =fopen("./.cdb/cdb.track","rb");
			rewind(fp);
			//while(!feof(fp))
			while(fread(&f,sizeof(struct trackst),1,fp))
		{
		
		//	fread(&f,sizeof(struct trackst),1,fp);
			printf("------\n");
			printf("name : %s  \nctime : %ld\nmtime : %ld\n checksum : %lu\n",f.name,f.ctime,f.mtime,f.checksum);
	 	}
		fclose(fp);
	}
	}
	else
	{
		printf("Error:unable to print tracking list\n");
		exit(1);
	}
	
}

int update(struct trackst *p)
{
	
	FILE *fp;
	struct trackst f;
	if(fp =fopen("./.cdb/cdb.track","r+b"))
	{
		while(fread(&f,sizeof(struct trackst),1,fp))
			{
			
				if(!strcmp(p->name,f.name))
				{
					printf("\n new time : %ld\n",p->mtime);
					if(p->checksum!=f.checksum)
					{
						fseek(fp,-sizeof(struct trackst),SEEK_CUR);
						fwrite(p,sizeof(struct trackst),1,fp);
					}
					fclose(fp);
					return 1;
					break;
					
				}
	
		
 			}
		
		
		
	}
	else
	{
		return 0;
	}
	
	
	
	
}