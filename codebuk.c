#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <dirent.h>
#include "./checks/checksum.h"
#include "./sha1/sha1.h"
#include "./dir/cdbdir.h"
#include "./track/cdbtrack.h"

#define FALSE 0
#define TRUE !FALSE

extern  int alphasort();  // for sorting filnames in ascending order
char pathname[MAXPATHLEN];

int main(int argc , char *argv[])
{
	FILE *fp;
	int len;
	int flag;
	unsigned int chks; // stores the checksum
	char buffer[8192] , placeholder[40]; // buffer for storing contents of file
	long int mtm;
	long int ctm;
	unsigned long chk;
	struct stat status;
	int count,i;
	struct direct **files;
	int file_select(struct direct *);  // file filter
	struct trackst *tp;
	
		
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
			struct trackst *tp;
			
	if(!flag)
	{	
		
		if(createtrack()==1)
		{
			printf("\n TRACKING INITIATED\n");
		
		}
		
	}
	if(argc==3)
	{
		if((tp=search(argv[2])))
		{
			printf("\n found checksum : %lu\n",tp->checksum);
		}
		else
			printf("No entry by name %s\n",argv[2]);
	}
	else
	{
		int clean =1;
		
		
		if (getwd(pathname) == NULL )
				{ printf("Error getting pathn");
						exit(0);
				}
		printf("Codebucket status for Directory: %s\n\n",pathname);
		count = scandir(pathname, &files, file_select, alphasort);
			   if(count <= 0)
				{		 printf("\nDirectory Empty\n");
						 printf("\n updating Directory list\n");
						exit(0);
				}
				for (i=1;i<count+1;++i)
				{ 
				
					if((tp=search(files[i-1]->d_name)))
					{
						
						if(!(stat(files[i-1]->d_name,&status)))
						{
							
							mtm = status.st_mtime;
							if(tp->mtime!=mtm)
							{
								printf("new time : %ld  old time : %ld  name:%s\n",mtm,tp->mtime,tp->name);
								printf("MODIFIED: %s\n",files[i-1]->d_name);
								clean=0;
							}
						}
						
						
					}
					else
						{
						if(!(opendir(files[i-1]->d_name)))     // filtering directories
						{	
						
							printf("NEW: %s\n",files[i-1]->d_name);
							clean=0;
						
						}							
							
							
							}
							
				
							
				}
				if(clean==1)
				{
					printf("Working directory clean\n");
				}
		
		
		
		
		printf("\n debug summary\n");	
	
	printtl();	
		
}		
		
		
}
		
		else if( !strcmp(argv[1],"add"))
		{
			struct trackst *tp;
			
			if(argc ==2)
			{
				
				printf("\n ERROR : no filenmae supplied \n");
				exit(1);
			}
		
		
			if(!strcmp(argv[2],"."))
			{
				struct trackst holder;    // temp holder
				if (getwd(pathname) == NULL )
						{ printf("Error getting pathn");
								exit(0);
						}
				count = scandir(pathname, &files, file_select, alphasort);
					   if(count <= 0)
						{		 printf("\nWorking Directory empty\n");
								 
								exit(0);
						}
						for (i=1;i<count+1;++i)
						{ 
							/*	if((fp=fopen(files[i-1]->d_name,"r"))==NULL)
								{
										printf("\n %s : no such file or directory found\n",argv[2]);
										exit(1);
								}*/
							
									//tp = (struct trackst *)malloc(sizeof(struct trackst));
							if((tp=search(files[i-1]->d_name)))
							{
								
								if(!(stat(files[i-1]->d_name,&status)))
								{
								
									mtm = status.st_mtime;
								
									//tp->mtime!=mtm
									if(1)
									{
									    	
											fp=fopen(files[i-1]->d_name,"r");
											mtm = status.st_mtime;
											ctm = status.st_ctime;
											len = fread(buffer,sizeof(char),sizeof(buffer),fp);
											fclose(fp);
											chk = checksum(buffer,len,0);
											strcpy(holder.name,files[i-1]->d_name);
											holder.ctime = ctm;
											holder.mtime = mtm;
											holder.checksum = chk;
											if(!update(&holder))
											{
												printf("\n Error: unable to update track list\n");
												exit(1);
											}
											else
											{
													printf("updated : %s\n",files[i-1]->d_name);
											}
				
									}
									
								}
								
								else
									{
										printf("\nError: unable to read kernel tables  #1\n");
									}	
							}		
								
							else
							{
								
									struct trackst ts;
									
									if(!(opendir(files[i-1]->d_name)))
									{
										
										if(!(stat(files[i-1]->d_name,&status)))
										{
											mtm = status.st_mtime;
											ctm = status.st_ctime;


											fp=fopen(files[i-1]->d_name,"r");
											len = fread(buffer,sizeof(char),sizeof(buffer),fp);
											chk = checksum(buffer,len,0);
											fclose(fp);

										strcpy(ts.name,files[i-1]->d_name);
										ts.ctime = ctm;
										ts.mtime = mtm;
										ts.checksum = chk;
										//printf("\n checkpoint #302\n");
										if(addfile(&ts)==-1)
										{
										//	printf("\n error?\n");
											//printf("Error: updating tracking list #2\n");
										}
										else
										{
											printf("Added : %s\n",files[i-1]->d_name);
											//printtl();
										}

										}
										
										else
											{
												printf("\nError: unable to read kernel tables #2\n");
											}
									
									}
									
									
									
									
									
									
							}
							
							fclose(fp);
						
						}
								
				
								
								
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
	
int file_select(struct direct *entry)

	{
		if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0)|| (entry->d_name[0]=='.'))
					return (FALSE);
					
					else
						return (TRUE);
	}
	
	
	
	
	
	
	
	
	
