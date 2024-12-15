#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include "file_operations.h"

// Dosya kopyalama fonksiyonu
int copy_file(const char *source, const char *destination) {
    FILE *src, *dest;
    char buffer[1024];
    size_t bytesRead;

    src = fopen(source, "rb");
    if (!src) {
        perror("Error opening source file");
        return -1;
    }

    dest = fopen(destination, "wb");
    if (!dest) {
        perror("Error opening destination file");
        fclose(src);
        return -1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytesRead, dest) != bytesRead) {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            return -1;
        }
    }

    fclose(src);
    fclose(dest);
    return 0;
}

// Dosya veya dizin taşıma fonksiyonu
int move_file_or_directory(const char *source, const char *destination) {
    struct stat st;
    char new_path[PATH_MAX];

    if (stat(source, &st) != 0) {
        perror("Source path does not exist");
        return -1;
    }

    if (stat(destination, &st) == 0 && S_ISDIR(st.st_mode)) {
        snprintf(new_path, sizeof(new_path), "%s/%s", destination, basename((char *)source));
    } else {
        strncpy(new_path, destination, sizeof(new_path));
    }

    if (rename(source, new_path) == 0) {
        return 0; 
    } else if (errno == EXDEV) {
        if (copy_file(source, new_path) == 0) {
            if (remove_file_or_directory(source) == 0) {
                return 0; 
            } else {
                perror("Failed to remove source after copying");
                return -1;
            }
        } else {
            perror("Failed to copy file across filesystems");
            return -1;
        }
    } else {
        perror("Error moving file or directory");
        return -1;
    }
}

// Dosya veya dizin silme fonksiyonu
int remove_file_or_directory(const char *path) {
    struct stat st;

    if (stat(path, &st) != 0) {
        perror("Path does not exist");
        return -1;
    }

    if (S_ISDIR(st.st_mode)) {
        if (rmdir(path) == 0) {
            return 0; 
        } else {
            perror("Failed to remove directory");
            return -1;
        }
    } else {
        if (remove(path) == 0) {
            return 0; 
        } else {
            perror("Failed to remove file");
            return -1;
        }
    }
}

// Yeni dosya oluşturma fonksiyonu
int create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file) {
        fclose(file);
        return 0; 
    }
    perror("Failed to create file");
    return -1; 
}

