#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "permissions.h"

// Dosya veya dizin izinlerini değiştirme fonksiyonu
int change_permissions(const char *path, const char *permissions) {
    int mode = strtol(permissions, NULL, 8); 

    if (chmod(path, mode) != 0) {
        perror("Error changing permissions");
        return -1; 
    }
    return 0; 
}

