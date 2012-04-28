/**
copyright (c) psych0der
checksum program with positional integrity 
*/


#include "checksum.h"

unsigned int checksum(char *buf,size_t len,int seed) // seed is used when recursively appending checksums
{
	int i=0;
	
		for(i;i<len;i++)
		{
			seed += (i+1)*(unsigned int)buf[i];
			
		}

return seed;
	
}






