#pragma once 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
const int buffer_size = 64;
struct io_file{
    int file_note;
    char buffer[buffer_size];
    int size = 0;
    int capacity = buffer_size;
};
typedef io_file my_FILE;


my_FILE* my_fopen(const char* filename,const char* );

void my_fwrite(const void* buffer,int size,my_FILE* stream);

int my_fflush();

void my_fclose(my_FILE* stream);
