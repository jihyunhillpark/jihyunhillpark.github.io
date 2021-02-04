/*
Author  : jihyun Park
Date    : 2020.03.28
Purpose : OS Practice - Parse user request command and Write mini shell program by child process. 
Title   : practice1 - getting process information.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>			 
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

//global variables
char buffer[BUFFER_SIZE]; 
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len) {
	int i = 0;
	int j = 0; 
	int ret = 0;
	
	// if current position is 0, reset buffer size and pos 
	if(lseek(fd, 0,  SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;
	while(j < max_len - 1){ 
		if(buffer_pos == buffer_size){
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
		}
		if(buffer_size == 0){
			if(j == 0)
				ret = EOF;
			break;
		}
		
		while(j < max_len - 2
		&& buffer_pos < buffer_size){
			str[j++] = buffer[buffer_pos++];
			if(str[j - 1] =='\0' || str[j - 1] == 10){
		 		j--; 
				max_len = j; 
				break;
		 	}
		}
	}
	str[j] = 0; 
	return ret;
}
int print_cpuinfo(int* cpu_nums, char* model)
{
    int cpu_info;
	char cpu_info_buf[BUFFER_SIZE];
	char *str1 = "cpu cores", *str2 = "model name",*ptr = NULL,*model_name=NULL;
	
	if((cpu_info = open("/proc/cpuinfo", O_RDONLY)) > 0 )
	{            
		while(ReadTextLine(cpu_info,cpu_info_buf, BUFFER_SIZE)== 0)
		{   
			 if(strncmp(cpu_info_buf, str1, 8) == 0)
             {	 
			 	sscanf(cpu_info_buf,"%*s %*s %*s %d", cpu_nums);
			 }
			 else if(strncmp(cpu_info_buf, str2, 10) == 0)
			 {	
			 	ptr = malloc(sizeof(char)*strlen(cpu_info_buf));
				strcpy(ptr,cpu_info_buf);
				
				model_name = strstr(ptr,":");
				model_name++;
			 }
		}
		printf("# of processor cores =  %d\n", *cpu_nums);
		printf("CPU model = %s\n", model_name); 
		free(ptr);
		close(cpu_info);
    }   
	else{
	    printf("Cannot open file");
	}
}
void print_meminfo(int* memtotal)
{
	int mem_info;
	char mem_info_buf[BUFFER_SIZE];
	char *str3 = "MemTotal";

	if((mem_info = open("/proc/meminfo", O_RDONLY))>0)
	{
		while(ReadTextLine(mem_info, mem_info_buf, BUFFER_SIZE)==0)
		{
			if(strncmp(mem_info_buf, str3, 8)==0)
			{
				sscanf(mem_info_buf, "%*s %d",memtotal);
				printf("MemTotal = %d\n", *memtotal);

			}
		}
		close(mem_info);
	}
	else{
		printf("Cannot open file");
	}
}
void print_loadavg(float loadavg[])
{
	int load_avg;
	char load_info_buf[BUFFER_SIZE];
	int i = 0;

	if((load_avg = open("/proc/loadavg", O_RDONLY))>0)
	{
		if(ReadTextLine(load_avg,load_info_buf, BUFFER_SIZE) ==0 )
		{
			sscanf(load_info_buf, "%f %f %f",&loadavg[0],&loadavg[1],&loadavg[2]);
			printf("loadavg1 = %f, loadavg2 = %f, loadavg3 = %f\n", loadavg[0],loadavg[1],loadavg[2]);
		}
	}
	else{
		printf("Cannot open file");
	}
} 
int main(){
	int cpu_info;
	char cpu_info_buf[BUFFER_SIZE];
	char *str1 = "cpu cores", *str2 = "model name", *model_name=NULL;
	int cpu_nums,memtotal;
	float loadavg[3];

	print_cpuinfo(&cpu_nums,model_name);
	print_meminfo(&memtotal);
	print_loadavg(loadavg);

}
