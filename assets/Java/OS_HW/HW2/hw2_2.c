/*
Author  : jihyun Park
Date    : 2020.03.28
Purpose : OS Practice - Parse user request command and Write mini shell program by child process. 
Title   : practice2 - parsing user request
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command, int *argc, char *argv[]); 

int main(){
	char command[MAX_CMD]; 
	command[0]=command[MAX_CMD-1]=0; //forsafety
	
	int argc = 0;
	char *argv[MAX_ARG] = { NULL };

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin); 
		command[strlen(command)-1] = 0; // trim \r
	
		if(strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) break;
		
		ParseCommand(command, &argc, argv);
		
		printf("argc = %d\n", argc); 
		for(int i = 0; i < argc; i++)
	 		printf("argv[%d] = %s\n", i, argv[i]);
		printf("argv[%d] = %p\n", argc, argv[argc]); //argv[argc] must be NULL
	}
	
	printf("Bye!\n");
 	return 0; 
}
void ParseCommand(char *command, int *argc, char *argv[])
{
	int i,j = 0, count = 0, ending = strlen(command);
	char *start, *pos = NULL;
	
	(*argc) = 0;
	start = pos = command; 
	for( i ;(*start) == 32;i++)
		pos=++start;

	for( j = i ; j < ending ;j++)
	{
		if((*pos == 32) && (count == 0)){
			*pos = 0;
			if(*(++pos) != 32)
			{
				argv[*argc] = start;
				start = pos;
				(*argc)++;
				if((*pos == 34)|| (*pos == 39))
				{
					(*start) = 0;
					start++;
					count=1;
				
				}
			}
   		}
		else if(count==1)
		{
			++pos;
			if((*pos == 34)|| (*pos == 39))
			{
				(*pos) = count = 0;
			}
		}
		else
		{   
			pos++;
			if(j == ending-1){
	          argv[*argc] = start;
			  (*argc)++;	
			}

		}
	}
	argv[*argc]= start = pos = NULL;
}
