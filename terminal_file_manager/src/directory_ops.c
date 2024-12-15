#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/stat.h> 
#include "directory_ops.h"

// Dizin içeriğini listeleyen fonksiyon
int list_directory(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return -1; 
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name); 
    }

    closedir(dir);
    return 0;
}

// Dizin içinde arama fonksiyonu
int search_file_or_directory(const char *path, const char *name) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, name) == 0) {
            closedir(dir);
            return 0; 
        }
    }

    closedir(dir);
    return -1; 
}

// Yeni dizin oluşturma fonksiyonu
int create_directory(const char *path) {
    if (mkdir(path, 0755) == 0) {
        return 0; 
    }
    return -1; 
}

// Dosya görüntüleme fonksiyonu
int view_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return -1;

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}

