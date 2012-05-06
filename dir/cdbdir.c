#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream> // for cin function (fgets) not working #strange#
#include <sys/stat.h>
#include <sys/param.h>     // for MAXPATHLEN MACRO
#include <unistd.h>
#include <ctype.h>
#include "cdbdir.h"



int destroycdb(void)
{
	
	if(access("./.cdb",F_OK) ==-1)
	{
		printf("\n either codebucket is not initialized or you are in project subdirectory\n");
		printf("Please move to project root irectory to remove codebucket\n");
		
	}
	
	else
	{
		char choice[6],buff[20];
		int i;
		printf("Are you sure you want to destroy codebucket ? (This is an irreversible instruction) Yes/No\n");
		scanf("%s",choice);
		for(i=0;i<3;i++)
		{
			choice[i] = tolower(choice[i]);
		}
		
		
		if(!strcmp(choice,"yes"))
		{
			sprintf(buff,"rm -rf .cdb .cdbblacklist");
			system(buff);
		}
		
		else if(strcmp(choice,"no"))
		{
			printf(" invalid input please try again \n");
		}
	}
	
}



int getconfig(void)
{
	char name[30],email[30],desc[200];
	FILE *fp;
	
	printf("Please provide details for creating configuration file\n");
	printf("Name: ");
	scanf("%s",name);
	printf("Email-id :");
	scanf("%s",email);
	
	if((fp = fopen("./.cdb/config","w"))!=NULL)
	{
		
		
		fprintf(fp,"[default-user]\n");
		fprintf(fp,"\tName : %s\n",name);
		fprintf(fp,"\tEmail : %s\n",email);
		fclose(fp);
		printf("configuration files successfully written\n");
		
		
	}
	else
	{
		printf("\n Error: unable to write to configuration files\n");
		exit(1);
	}
	
	printf("Please provide description of the project: - \n");
	//scanf("%s",desc);
	fflush(stdin);
	scanf("%s",desc);
	printf("\n desc : %s\n",desc);
	
	if((fp = fopen("./.cdb/descr","w"))!=NULL)
	{
		
		
		fprintf(fp,"[project-description]\n");
		fprintf(fp,"%s",desc);
		fclose(fp);
		printf("project description successfully written\n");
		
		
	}
	else
	{
		printf("\n Error: unable to write project description\n");
		exit(1);
	}
	
	
	
}



int initcodebuk(void)
{
	char files[4][20] = {"HEAD","config","descr","index"};
	char buff[50],wd[MAXPATHLEN],ch; // wd for dtoring workig directory
	FILE *fl;
	int exists;

	getwd(wd);// get the path of working directory
	exists = access("./.cdb",F_OK); // to check if it is already initialized


	if(exists != -1)
	{
		printf("codebucket is alredy initialized\n");
		printf("Do you want to reinitialize codebucket\n(this option will delete previous contents of codebucket)\n y(yes) / n(no)\n");
		scanf("%c",&ch);
		if(tolower(ch)=='y')
		{
			destroycdb();
		}
		if(tolower(ch)=='n')
		{
			exit(1);
		}
	}
	sprintf(buff,"mkdir .cdb");
	if(!system(buff))
	{
		fl=fopen(".cdbblacklist","w"); // create ignore file
		fclose(fl);
		
		strcpy(buff,""); // empty the buffer
		sprintf(buff,".cdb");
		if(!chdir(buff))
		{
			strcpy(buff,"");
			sprintf(buff,"mkdir logs objs refs");
			if(!system(buff))
			{
				int i;
				for(i=0;i<4;i++)
				{
					fl=fopen(files[i],"w");
					fclose(fl);
				}
				
				printf("codebucket suucessfully initilized in :%s\n",wd);
				chdir(wd);
				getconfig();
			
				return 1;
			}
			
			else return -1;
			
			
		}
		else return -1;
		
	}
	
	else
	{
		return -1;
	}
	
	
}



