struct trackst
{
	char name[20];
	unsigned long checksum;
	long int mtime;
	long int ctime;
	
};


int filecheck(void);
int createtrack(void);
int writetrack(void);
int readcontents(void);
int addfile(struct trackst *);
void printtl(void);
struct trackst * search(char*);