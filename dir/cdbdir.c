#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "cdbdir.h"


int initcodebuk(void)
{
	char files[4][20] = {"HEAD","config","descr","index"};
	char buff[50];
	FILE *fl;
	sprintf(buff,"mkdir .cdb");
	if(!system(buff))
	{
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