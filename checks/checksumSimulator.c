/**
copyright (c) psych0der
checksum program with positional integrity 
*/

#include <stdio.h>
#include <stdlib.h>
#include "checksum.h"

int main(int argc,char *argv[])
{
	char buffer[8192];
	FILE *fp;
	unsigned int checks;
	int len;
	char cs[10];
	
	if(!(fp=fopen(argv[1],"r")))
	{
		printf("\n an error occurred while opening the file\naborting the program \n");
	}
	else
	{
		len = fread(buffer,sizeof(char),sizeof(buffer),fp);
		checks = checksum(buffer,len,0);
		sprintf(cs,"%d",checks);
		printf("cheksum is %s\n",cs);
		
	}
	
	return 0;
	
	
}
