

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sha1.h"

int main(int argc , char *argv[])
{
    SHA1Context sha;
    int i;
	char sha1hash[70];
	int num =2;
	char ulstring[70];
	sha1hash[0]='\0';
	char command[100];
   

    SHA1Reset(&sha);
    SHA1Input(&sha, (const unsigned char *) argv[1], strlen(argv[1]));

    if (!SHA1Result(&sha))
    {
        fprintf(stderr, "ERROR-- could not compute message digest\n");
    }
    else
    {
        printf("\t");
        for(i = 0; i < 5 ; i++)
        {
            sprintf(ulstring,"%X", sha.Message_Digest[i]);
			strcat(sha1hash,ulstring);
			
        }	
        
    }

	printf("\n");
	printf("\t%s\n",sha1hash);

    return 0;
}
