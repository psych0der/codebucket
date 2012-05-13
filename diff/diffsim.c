#include <stdio.h>
#include <stdlib.h>
#include "diff.h"

int main(int argc , char *argv[])
{
	if(argc <3)
	{
		printf("\n F*** OFF\n");
		exit(1);
	}
	diff(argv[1],argv[2]);
	
	
	
	
	printf("\n");
	return 0;
}


