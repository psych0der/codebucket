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
#include "./commit/commit.h"
#include "./track/cdbtrack.h"
#include "./diff/diff.h"

#define FALSE 0
#define TRUE !FALSE

extern  int alphasort();  // for sorting filnames in ascending order
int match(struct direct ** , char *,int);
char * substr(char *, int, int ) ;

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
			int num,i=0;
			if(!flag)
			{	

				if(createtrack()==1)
				{
					printf("\n TRACKING INITIATED\n");

				}

			}
		
			
	/*************************** CLEANING *******************************/
	
	
	
			if (getwd(pathname) == NULL )
					{ printf("Error getting path\n");
							exit(0);
					}
			
			count = scandir(pathname, &files, file_select, alphasort);
			num = readcontents();
			char flnames[num][20];
			getnames(flnames);
			
			
			for(i=0;i<num;i++)
			{
				//printf("filename : %s\n",flnames[i]);
				if(!(match(files,flnames[i],count)))
				{
					untrack(flnames[i]);
				}
			}
	
	
	
	/*********************************************************************/		
			
			
	
	
			
	
	if(argc==3)
	{
		if(!strcmp(argv[2],"show"))
		{
			
			printtl();
			
		}
		
		
		else
		{
			if((tp=search(argv[2])))
			{
				printf("\n found checksum : %lu\n",tp->checksum);
			}
			else
			printf("No entry by name %s\n",argv[2]);
		}
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
								//printf("new time : %ld  old time : %ld  name:%s\n",mtm,tp->mtime,tp->name);
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
		
		
		
		
	//	printf("\n debug summary\n");	
	
	//printtl();	
		
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
	
		
		else if(!strcmp(argv[1],"untrack"))
		{
			
			untrack(argv[2]);
			
			
			
			
		}
		
		else if( !strcmp(argv[1],"commit"))
		{
			//printf("\n lol\n");
			if(argc<3)
			{
				printf("\nPlease provide commit message with commit command\n");
				exit(1);
			}
		
			unsigned long checks,sum=0;
						SHA1Context sha;
				    	int i,u,j;
				        char sha1hash[70];
				        int num =2;
				        char ulstring[70];
				        sha1hash[0]='\0';
				        char command[100]; 
						//int num;
						FILE *fp,*fp1,*fp2;
						char folder[3],file[39],compath[40],flpath[50],treepath[50],treehash[50];
						char parhash[50];
						
						num = readcontents();
						char flnames[num][20]; 
						char objhash[num][50];
						getnames(flnames);
					
						for(u=0;u<num;u++)
						{
							
							strcpy(placeholder,"");
							printf(" filename : %s\n",flnames[u]);
							if((fp=fopen(flnames[u],"r"))!=NULL)
							{
								/*  checksum */
								len = fread(buffer,sizeof(char),sizeof(buffer),fp);
								//fclose(fp);
							
								chks = checksum(buffer,len,0);
								sum+=(unsigned long)chks;
								sprintf(placeholder,"%u",chks);
								printf("checksum : %s\n",placeholder);
									
								/* hash */
								SHA1Reset(&sha);
							    SHA1Input(&sha, (const unsigned char *) placeholder, strlen(placeholder));
								
							    if (!SHA1Result(&sha))
							    {
							        fprintf(stderr, "ERROR-- could not compute message digest\n");
							    }
							    else
							    {
							        
									//printf("\t");
							        for(i = 0; i < 5 ; i++)
							        {
										sprintf(ulstring,"%X", sha.Message_Digest[i]);
										                        strcat(sha1hash,ulstring);

										printf(" u  %d\n",u);
									}
								

								}
							
									
								strcpy(objhash[u],sha1hash);
								printf("hash %s\n",sha1hash);
								strcpy(folder,substr(sha1hash,1,2));
								strcpy(file,substr(sha1hash,3,38));
								strcpy(compath,"./.cdb/objs/");
								strcat(compath,folder);
							    printf("\n line #546\n");
								if(!opendir(compath))     
								{
									//printf("\n compath\n");
									sprintf(command,"mkdir ./.cdb/objs/%s",folder);
									system(command);
							
								}
								strcat(compath,"/");
								strcat(compath,file);
								if((fp1 = fopen(compath,"wb"))!=NULL)
								{
									fwrite(buffer,sizeof(char),sizeof(buffer),fp1);
									printf("\n writing\n");
									
								}
								else
								{
									printf("Error:unable to create blob\n");
								}
								fclose(fp1);
								//fclose(fp);
							
									
									
					 		}
							else
							{
								printf("****Error: unable to open file %s\n",flnames[u]);
							}
						printf("\n hehehe\n");	
						//fclose(fp2);
							
						}
						
				
			
				
				
				/*********    THIS PART IS FOR WRITING TREE OBJECT      ******************/
				
				sprintf(placeholder,"%ld",sum);
				SHA1Reset(&sha);
			    SHA1Input(&sha, (const unsigned char *) placeholder, strlen(placeholder));

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
				strcpy(treehash,sha1hash);
				strcpy(folder,substr(sha1hash,1,2));
				strcpy(file,substr(sha1hash,3,38));
				strcpy(compath,"./.cdb/objs/");
				strcat(compath,folder);
				if(!(opendir(files[i-1]->d_name)))     
				{
					sprintf(command,"mkdir ./.cdb/objs/%s",folder);
					system(command);
			
				}
				strcat(compath,"/");
				strcat(compath,file);
				if((fp1 = fopen(compath,"wb"))!=NULL)
				{
					int h=0;
					struct treeblob tb;
					fwrite(&num,sizeof(int),1, fp);
					for(h=0;h<num;h++)
					{
						tb.type=1;
						strcpy(tb.hash,objhash[h]);
						strcpy(tb.fname,flnames[h]);
					
						
						fwrite(&tb,sizeof(struct treeblob),1,fp1);
						
						
					}
					
				
					
				}
				else
				{
					printf("Error:unable to create TREE object\n");
				}
				fclose(fp1);
				//fclose(fp);
				
			
			
			
			
			
			/***************************************************************************/	
			
			
			/***********COMMIT DATA ***********************/
			
		sprintf(placeholder,"%ld",sum);
		strcat(placeholder,"CODEBUCKETSIGNATURE"); // to privide random commits
		SHA1Reset(&sha);
	    SHA1Input(&sha, (const unsigned char *) placeholder, strlen(placeholder));
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
	
		strcpy(folder,substr(sha1hash,1,2));
		strcpy(file,substr(sha1hash,3,38));
		strcpy(compath,"./.cdb/objs/");
		strcat(compath,folder);
		if(!(opendir(compath)))     
		{
			sprintf(command,"mkdir ./.cdb/objs/%s",folder);
			system(command);
	
		}
		strcat(compath,"/");
		strcat(compath,file);
		if((fp1 = fopen(compath,"wb"))!=NULL)
		{
			struct commitdata cd;
			FILE *fp3;
			fp3 = fopen("./.cdb/HEAD","r");
			fscanf(fp3,"%s",parhash);
			fclose(fp3);
			strcpy(cd.parent,parhash);
			strcpy(cd.tree,treehash);
			strcpy(cd.msg,argv[2]);
			fwrite(&cd,sizeof(struct commitdata),sizeof(buffer),fp1);
			fp3 = fopen("./.cdb/logs/log","a");
			fprintf(fp3,"<%s>\n<CURRENT DATE>\n<%s>\n---------------",sha1hash,cd.msg);
			fclose(fp3);
			fp3 = fopen("./.cdb/HEAD","w");
			fprintf(fp3,"%s",sha1hash);
			fclose(fp3);
			
		}
		else
		{
			printf("Error:unable to commit data blob\n");
		}
		fclose(fp1);
	//	fclose(fp);
		
	
			
			
			
			
			
			
	/****************************************************************************************/
			
			
			
	}
			
			
			
			
	else if(!strcmp(argv[1],"diff"))
	{
		if(argc<4)
		{
			printf("\n incorrect usage-- please refer to manual\n");
		}
		else
		{
			diff(argv[2],argv[3]);
		}
		
	}						
	
	
	else
	{
		printf("\nError: incorrect usage\n");
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
	
int match(struct direct **files , char *name,int count)	
{
	int i=0;
	for(i;i<count;i++)
	{
	//	printf("\n fl:%s   name:%s\n",files[i]->d_name,name);
		
		if(!strcmp(name,files[i]->d_name))
		{
			//printf("\n matched %s\n",name);
			return 1;
		}
	}
	return 0;
	
	
	
}

char *substr(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = (char *)malloc(length+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(EXIT_FAILURE);
   }
 
   for (c = 0 ; c < position -1 ; c++) 
      string++; 
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}

	
	
	
	
	
	
	
