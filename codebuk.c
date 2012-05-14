#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "./checks/checksum.h"
#include "./sha1/sha1.h"
#include "./dir/cdbdir.h"
#include "./track/cdbtrack.h"

int main(int argc , char *argv[])
{
	FILE *fp;
	int len;
	int flag;
	unsigned int chks; // stores the checksum
	char buffer[8192] , placeholder[40]; // buffer for storing contents of file
	
	
		
	if(argc ==1)
	{
		printf("ERROR: insufficient arguments supplied .. refer to the manual\n");
		exit(1);
	}
	

	if(!strcmp(argv[1],"ini"))
	{
		
		if(initcodebuk()==-1)    // calls function to create directoy structure
		{
			printf(" ERROR: unable to initialize codebucket !\n");
		}
		
	}


	else if( !strcmp(argv[1],"checksum")) 
		{
			if(!(fp=fopen(argv[2],"r")))
			{
				printf("\n %s : no such file or directory found\n",argv[2]);
			}
			else if(argc==2)
			{
				printf("\n ERROR: No file name specified\n");
				exit(1);
			}
			
			else
			{
				len = fread(buffer,sizeof(char),sizeof(buffer),fp);
				chks = checksum(buffer,len,0);
				sprintf(placeholder,"%d",chks);
				printf("%s\n",placeholder);
			}
			
			
			
		}
		
	else if( !strcmp(argv[1],"hash")) 
		
		{
			if(argc ==2)
			{
				
				printf("\n ERROR : no string supplied \n");
				exit(1);
			}
			    
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
		
		
else if(!strcmp(argv[1],"status"))
{
			int flag;
			flag = filecheck();
			
	if(!flag)
	{	
		
		if(createtrack()==1)
		{
			printf("\n TRACKING INITIATED\n");
		
		}
		
	}
	
//	writetrack();
//	printf("contents : %d\n",readcontents());
	printtl();	
		
		
		
		
}
		
		else if( !strcmp(argv[1],"add"))
		{
			if(argc ==2)
			{
				
				printf("\n ERROR : no filenmae supplied \n");
				exit(1);
			}
			else
			{
			
				char fname[20];
				strcpy(fname,argv[2]);
				long int mtm;
				long int ctm;
				unsigned long chk;
				struct stat status;
				struct trackst ts;
			
			if((fp=fopen(argv[2],"r"))==NULL)
			{
					printf("\n %s : no such file or directory found\n",argv[2]);
					exit(1);
			}
			else
			{
				if(!(stat(argv[2],&status)))
				{
					mtm = status.st_mtime;
					ctm = status.st_ctime;
					
					
					
						len = fread(buffer,sizeof(char),sizeof(buffer),fp);
						chk = checksum(buffer,len,0);
						
					
					strcpy(ts.name,fname);
					ts.ctime = ctm;
					ts.mtime = mtm;
					ts.checksum = chk;
					if(addfile(&ts)==-1)
					{
						//printf("Error: updating tracking list #2\n");
					}
					else
					{
						printf("tracking list updated\n");
						printtl();
					}
				
				}
				else
				{
					printf("\n Error : unable to access kernel tables\n");
					exit(1);
				}
				
			}	
			
			}
			
		} 
		
		
		
			
				return 0;	
		
	}
	
	
	
	
	
	
	
	
	
