#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>

int copy_file(const char *source, const char *destination);
int move_file_or_directory(const char *source, const char *destination);
int remove_file_or_directory(const char *path);
int create_file(const char *path);
int create_directory(const char *path);
int view_file(const char *path);
int list_directory(const char *path);
int search_file_or_directory(const char *path, const char *name);
int change_permissions(const char *path, const char *permissions);

#endif 

