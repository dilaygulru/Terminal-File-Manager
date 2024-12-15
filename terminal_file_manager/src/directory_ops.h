#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

#include <stdio.h>

int list_directory(const char *path);
int search_file_or_directory(const char *path, const char *name);
int create_directory(const char *path);
int view_file(const char *path);

#endif 

