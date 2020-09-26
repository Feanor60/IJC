#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LSIZ 1023
#define RSIZ 8

int main(void) 
{
    char line[RSIZ][LSIZ];
	char fname[20];
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;
    printf("\n\n Read the file and store the lines into an array :\n");
	printf("------------------------------------------------------\n"); 
	printf(" Input the filename to be opened : ");
	scanf("%s",fname);	

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr) != NULL) 
	{
        line[i][strlen(line[i]) - 1] = '\0';//
		 printf(" %s\n", line[i]);
        i++;
    }
    tot = i;
	// printf("\n The content of the file %s  are : \n",fname);    
    // for(i = 0; i < tot; ++i)
    // {
    //     printf(" %s\n", line[i]);
    // }
	printf("%c", line[0][strlen(line[0])]);
    printf("\n");
    return 0;
}