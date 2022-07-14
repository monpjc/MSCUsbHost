#include "mbed.h"
#include "MSCFileSystem.h"
//#include <stat.h>

#define FSNAME "msc"
MSCFileSystem msc(FSNAME);

int main()
{
	DIR *d;
	struct dirent *p;
	//struct stat st;
	//char path[PATH_MAX];
    
    printf("\n\n================================\n");
    printf("USB Mass storage demo program for mbed LPC1768\n");
    printf("================================\n\n");
    
	d = opendir("/" FSNAME);
    
    printf("\nList of files on the flash drive:\n");
    if ( d != NULL )
    {
        while ( (p = readdir(d)) != NULL )
        {
        	printf(" - %s\n", p->d_name);
        	/* no <stat.h> on mbed, it seems :/
        	sprintf(path, "/"FSNAME"/%s", p->d_name);
        	if ( stat(path, &st) == 0 )
        	{
        	  if ( S_ISDIR(st.st_mode) )
        	    printf(" <directory>\n");
        	  else
        	    printf(" %d\n", st.st_size);
        	}
        	else
        	{
        	  printf(" ???\n");
        	}*/
        }
    }
    else
    {
    	error("Could not open directory!");
    }
    printf("\nTesting file write:\n");
    FILE *fp = fopen( "/" FSNAME "/msctest.txt", "w");
    if ( fp == NULL )
    {
        error("Could not open file for write\n");
    }
    fprintf(fp, "Hello mass storage!");
    fclose(fp); 
    printf("\n - OK\n");

    printf("\nTesting file read:\n");
    fp = fopen( "/" FSNAME "/msctest.txt", "r");
    if ( fp == NULL )
    {
        error("Could not open file for read\n");
    }
    char buf[256];
    if ( NULL == fgets(buf, sizeof(buf), fp) )
    {
        error("Error reading from file\n");
    }
    fclose(fp); 
    printf("\n - OK, read string: '%s'\n\n", buf);
}
