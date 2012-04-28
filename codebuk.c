#include <string.h>
#include <unistd.h>
#include "./checks/checksum.h"
#include "./sha1/sha1.h"

int main(int argc , char *argv[])
{
	FILE *fp;
	int len;
	unsigned int chks; // stores the checksum
	char buffer[8192] , placeholder[40]; // buffer for storing contents of file
	
	
		
	if(argc ==1)
	{
		printf("\n insufficient arguments supplied\n");
		exit(1);
	}
	
	if( !strcmp(argv[1],"checksum")) 
		{
			if(!(fp=fopen(argv[2],"r")))
			{
				printf("\n %s : no such file or directory found\n",argv[2]);
			}
			else
			{
				len = fread(buffer,sizeof(char),sizeof(buffer),fp);
				chks = checksum(buffer,len,0);
				sprintf(placeholder,"%d",chks);
				printf("%s\n",placeholder);
			}
			
			
			
		}
		
	else	if( !strcmp(argv[1],"hash")) 
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
						
		
							
		}
		
		
			
				return 0;	
		
	}
	
	
	
	
	
	
	
	
	
