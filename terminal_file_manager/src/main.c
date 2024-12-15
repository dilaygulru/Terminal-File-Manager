#include <stdio.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void print_help() {
    printf("Available commands:\n");
    printf("  1-slist [path] - List files and directories in a folder.\n");
    printf("  2-scopy [source] [destination] - Copy a file to a destination.\n");
    printf("  3-smove [source] [destination] - Move a file to a destination.\n");
    printf("  4-sremove [path] - Remove a file or directory.\n");
    printf("  5-screatefile [path] - Create a new file.\n");
    printf("  6-screatedir [path] - Create a new directory.\n");
    printf("  7-sview [path] - View the content of a file.\n");
    printf("  8-ssearch [path] [name] - Search for a file or directory by name.\n");
    printf("  9-schmod [path] [permissions] - Change file or directory permissions.\n");
    printf("  10-slog - Display the log of operations.\n");
    printf("  11-exit - Exit the program.\n");
}

int main() {
    char command[256];

    printf("Terminal Based File Manager\n");
    printf("Type 'help' for a list of commands.\n");

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; 

        if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strncmp(command, "slist", 5) == 0) {
            char *path = command + 6;
            if (strlen(path) == 0) {
                printf("Usage: slist [path]\n");
                printf("Error: Path is required.\n");
            } else if (list_directory(path) != 0) {
                printf("Error: Unable to open directory '%s'. Make sure the path is correct.\n", path);
            } else {
                write_log("List directory command executed successfully.");
            }
        } else if (strncmp(command, "scopy", 5) == 0) {
            char *args = command + 6;
            char *source = strtok(args, " ");
            char *destination = strtok(NULL, " ");
            if (source && destination) {
                if (copy_file(source, destination) == 0) {
                    printf("File successfully copied from '%s' to '%s'.\n", source, destination);
                    write_log("File copied successfully.");
                } else {
                    printf("Error: Could not copy file from '%s' to '%s'.\n", source, destination);
                    write_log("Error occurred while copying file.");
                }
            } else {
                printf("Usage: scopy [source] [destination]\n");
                printf("Error: Missing source or destination path.\n");
            }
        } else if (strncmp(command, "smove", 5) == 0) {
            char *args = command + 6;
            char *source = strtok(args, " ");
            char *destination = strtok(NULL, " ");
            if (source && destination) {
                if (move_file_or_directory(source, destination) == 0) {
                    printf("File successfully moved from '%s' to '%s'.\n", source, destination);
                    write_log("File moved successfully.");
                } else {
                    printf("Error: Could not move file from '%s' to '%s'.\n", source, destination);
                    write_log("Error occurred while moving file.");
                }
            } else {
                printf("Usage: smove [source] [destination]\n");
                printf("Error: Missing source or destination path.\n");
            }
        } else if (strncmp(command, "sremove", 7) == 0) {
            char *path = command + 8;
            if (strlen(path) == 0) {
                printf("Usage: sremove [path]\n");
                printf("Error: Path is required.\n");
            } else if (remove_file_or_directory(path) == 0) {
                printf("Successfully removed '%s'.\n", path);
                write_log("File or directory removed successfully.");
            } else {
                printf("Error: Could not remove '%s'. Ensure it exists and you have the necessary permissions.\n", path);
                write_log("Error occurred while removing file or directory.");
            }
        } else if (strncmp(command, "screatefile", 11) == 0) {
            char *path = command + 12;
            if (strlen(path) == 0) {
                printf("Usage: screatefile [path]\n");
                printf("Error: Path is required.\n");
            } else if (create_file(path) == 0) {
                printf("File '%s' created successfully.\n", path);
                write_log("File created successfully.");
            } else {
                printf("Error: Could not create file '%s'.\n", path);
                write_log("Error occurred while creating file.");
            }
        } else if (strncmp(command, "screatedir", 10) == 0) {
            char *path = command + 11;
            if (strlen(path) == 0) {
                printf("Usage: screatedir [path]\n");
                printf("Error: Path is required.\n");
            } else if (create_directory(path) == 0) {
                printf("Directory '%s' created successfully.\n", path);
                write_log("Directory created successfully.");
            } else {
                printf("Error: Could not create directory '%s'.\n", path);
                write_log("Error occurred while creating directory.");
            }
        } else if (strncmp(command, "sview", 5) == 0) {
            char *path = command + 6;
            if (strlen(path) == 0) {
                printf("Usage: sview [path]\n");
                printf("Error: Path is required.\n");
            } else if (view_file(path) != 0) {
                printf("Error: Could not view file '%s'.\n", path);
                write_log("Error occurred while viewing file.");
            } else {
                write_log("File viewed successfully.");
            }
        } else if (strncmp(command, "ssearch", 7) == 0) {
            char *args = command + 8;
            char *path = strtok(args, " ");
            char *name = strtok(NULL, " ");
            if (path && name) {
                if (search_file_or_directory(path, name) == 0) {
                    printf("Search completed successfully.\n");
                    write_log("File or directory search completed.");
                } else {
                    printf("Error: Could not find '%s' in '%s'.\n", name, path);
                    write_log("Error occurred during search.");
                }
            } else {
                printf("Usage: ssearch [path] [name]\n");
                printf("Error: Missing path or name.\n");
            }
        } else if (strncmp(command, "schmod", 6) == 0) {
            char *args = command + 7;
            char *path = strtok(args, " ");
            char *permissions = strtok(NULL, " ");
            if (path && permissions) {
                if (change_permissions(path, permissions) == 0) {
                    printf("Permissions for '%s' changed to '%s'.\n", path, permissions);
                    write_log("Permissions changed successfully.");
                } else {
                    printf("Error: Could not change permissions for '%s'.\n", path);
                    write_log("Error occurred while changing permissions.");
                }
            } else {
                printf("Usage: schmod [path] [permissions]\n");
                printf("Error: Missing path or permissions.\n");
            }
        } else if (strcmp(command, "slog") == 0) {
            if (display_log() != 0) {
                printf("Error: Could not display log.\n");
            }
        } else {
            printf("Unknown command: '%s'. Type 'help' for a list of commands.\n", command);
        }
    }

    return 0; 
}

