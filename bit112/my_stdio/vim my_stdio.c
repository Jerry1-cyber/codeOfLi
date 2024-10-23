#include "my_stdio.h"
my_FILE* my_fopen(const char* filename)
{
    my_FILE* newfile = (my_FILE*)malloc(sizeof(my_FILE));
    if(newfile == NULL) return NULL;
    int fd = open(filename,"w") 
}
