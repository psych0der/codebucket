/**
copyright (c) psych0der
checksum program with positional integrity 
header file
*/
#include <stdio.h>
#include <stdlib.h>

unsigned int checksum(char *buff,size_t len,int seed);

/*
*buff points to character buffer extraxted from read command
*size_t is automatically returned from read command
*/