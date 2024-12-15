# Terminal Based File Manager

## Project Overview
The Terminal Based File Manager is a C-based application that allows users to manage files and directories through a command-line interface. It performs common file operations such as listing, copying, moving, and deleting files and directories. The program utilizes system calls for Linux/Unix environments.

## Features
| Command                          | Description                                                   |
|-----------------------------------|---------------------------------------------------------------|
| `slist [path]`                    | List files and directories in the specified folder.           |
| `scopy [source] [destination]`    | Copy a file from source to destination.                       |
| `smove [source] [destination]`    | Move a file from source to destination.                       |
| `sremove [path]`                  | Remove a file or directory at the specified path.             |
| `screatefile [path]`              | Create a new file at the specified path.                       |
| `screatedir [path]`               | Create a new directory at the specified path.                 |
| `sview [path]`                    | View the content of the file at the specified path.           |
| `ssearch [path] [name]`           | Search for a file or directory by name in the specified path. |
| `schmod [path] [permissions]`     | Change file or directory permissions.                         |
| `slog`                            | Display the log of operations performed.                      |
| `exit`                            | Exit the program.                                             |

## Logger Path Configuration
Make sure to update the `logger.c` file to specify the correct log file path for your system. The path to the log file is hardcoded in the `logger.c` file, so you will need to modify it according to your desired location before running the program.

## How to Build and Run

### Requirements
- Linux/Unix environment
- GCC compiler
- Makefile (provided in the project)

### Building the Program
1. Navigate to the project directory in your terminal.
2. Run the following command to compile the program:
   ```bash
   make
   ```
   This will create an executable file in the `bin` directory.

### Running the Program
After building the project, you can run the program with the following command:
```bash
./bin/terminal_file_manager
```

The program will prompt you to enter commands for file and directory operations. Use the list of available commands as shown above to interact with the program.

### Example Commands
```bash
slist /home/user/documents
scopy /home/user/file.txt /home/user/documents/
sremove /home/user/documents/oldfile.txt
```

### Exiting the Program
To exit the program, type:
```bash
exit
```

## Project Structure

```plaintext
project_directory/
│
├── bin/
│   └── file_manager             # Executable file
├── src/
│   ├── main.c                   # Controls the flow of the program
│   ├── file_operations.c        # Handles file operations (read, write, copy, move)
│   ├── file_operations.h        # Header for file_operations.c
│   ├── directory_ops.c          # Manages folder operations (create, delete, list)
│   ├── directory_ops.h          # Header for directory_ops.c
│   ├── permissions.c            # Manages file/folder permissions
│   ├── permissions.h            # Header for permissions.c
│   ├── logger.c                 # Logs operations to a file
│   └── logger.h                 # Header for logger.c
├── operations.log               # Log file for operations
└── Makefile                    # Makefile to build the project

```

## Conclusion
This project offers a simple and effective way to manage files and directories through a terminal. It helps in understanding key system calls in Linux/Unix and provides an opportunity to develop modular and maintainable code.
