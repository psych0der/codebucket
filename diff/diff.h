struct hash_vec
{
	int lno;  // stores the line number
	unsigned long hash; // stores the hash
	
	struct hash_vec *next;

	
};

struct equiclass
{
	int lno;
	int last;   // 1 for true 0 for false
	
	
};

struct candidate
{
	int a;
	int b;
	struct candidate *ref;
	
};

void diff(char *,char*); // gets hash of individual lines of a file specifies by char *
void insert(int,unsigned long,struct hash_vec **,struct hash_vec **);
void printll(struct hash_vec *);
int adjustll(struct hash_vec *);
void sort(struct hash_vec *);
void getarray(struct hash_vec* , struct hash_vec*);
void printarray(struct hash_vec*,int);

int gete(struct hash_vec *,struct equiclass *);
void printel(struct equiclass *,int);



void fillp(int * , struct equiclass * , struct hash_vec*,struct hash_vec*,int,int);
int merge(struct candidate *,int *,int,struct equiclass *,int);