#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "logger.h"

// Log dosyasına yazma fonksiyonu
int write_log(const char *message) {
    const char *log_file_path = "/home/dilay/terminal_file_manager/operations.log"; 
    FILE *logFile = fopen(log_file_path, "a"); 

    if (!logFile) {
        perror("Error opening log file"); 
        printf("Error code: %d\n", errno); 
        return -1; 
    }

    fprintf(logFile, "%s\n", message); 
    fclose(logFile); 
    return 0; 
}


int display_log() {
    const char *log_file_path = "/home/dilay/terminal_file_manager/operations.log"; 
    FILE *logFile = fopen(log_file_path, "r"); 

    if (!logFile) {
        perror("Error opening log file"); 
        return -1; 
    }

    char line[256];
    while (fgets(line, sizeof(line), logFile)) { 
        printf("%s", line); 
    }

    fclose(logFile); 
    return 0; 
}

