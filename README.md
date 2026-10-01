# Linux Process Manager

A command-line process management tool written in C for Linux.

The project uses the Linux `/proc` filesystem and POSIX system calls to inspect, create, and control processes.

## Features

- List running processes
- Search processes by name
- Display process information
- Start new processes
- Support command-line arguments
- Terminate processes
- Pause processes
- Resume processes
- Input validation and error handling

## Technologies

- C
- Linux
- POSIX APIs
- `/proc` filesystem
- GCC
- Make

## Linux Concepts Used

- Process IDs (PID)
- Parent and child processes
- fork()
- execvp()
- kill()
- SIGTERM
- SIGSTOP
- SIGCONT
- /proc/<PID>/comm
- /proc/<PID>/status

## Project Structure

        linux-process-manager/
        ├── src/
        │   ├── main.c
        │   ├── process.c
        │   └── process.h
        ├── Makefile
        ├── README.md
        └── .gitignore

## Build

Make sure GCC and Make are installed.

Build the project using:

    make

Or compile manually:

    gcc -Wall -Wextra -std=c11 src/main.c src/process.c -o process_manager

## Run

    ./process_manager

## Usage

The program provides an interactive menu:

    ===== Linux Process Manager =====
    1. List Processes
    2. Search Process
    3. Process Information
    4. Start Process
    5. Terminate Process
    6. Pause Process
    7. Resume Process
    8. Exit

### List Processes

Displays the PID and name of running processes by reading the Linux /proc filesystem.

Example:

    PID        PROCESS
    --------------------------------------------
    1          systemd
    544        bash
    603        bash

### Search Process

Search for running processes by name.

Example:

    Enter choice: 2
    Enter process name: bash

    PID        PROCESS
    --------------------------------------------
    603        bash
    8231       bash

### Process Information

Displays information about a specific process.

Example:

    Enter choice: 3
    Enter PID: 544

    ===== Process Information =====
    Name:   bash
    State:  S (sleeping)
    Pid:    544
    PPid:   543
    Threads:        1

### Start Process

Creates a new child process using fork() and executes the requested command using execvp().

Example:

    Enter choice: 4
    Enter command: sleep 30
    Process created with PID: 8517

Command-line arguments are supported:

    ls -la
    sleep 30
    echo hello

### Terminate Process

Sends SIGTERM to a process.

Example:

    Enter choice: 5
    Enter PID: 8517
    Termination signal sent to process 8517.

### Pause Process

Stops a running process using SIGSTOP.

Example:

    Enter choice: 6
    Enter PID: 8517
    Process 8517 paused.

### Resume Process

Continues a stopped process using SIGCONT.

Example:

    Enter choice: 7
    Enter PID: 8517
    Process 8517 resumed.

## Error Handling

The program handles:

- Invalid menu input
- Invalid PIDs
- Non-existent processes
- Processes that cannot be accessed
- Invalid commands
- Failed process creation
- Failed process execution

## Requirements

- Linux environment
- GCC
- Make

The project can be run on a native Linux system or through WSL on Windows.

## Learning Goals

This project was built to gain practical experience with:

- Linux systems programming
- Process management
- Parent and child processes
- POSIX system calls
- Linux signals
- The /proc filesystem
- C programming
- Command-line application development

## Future Improvements

- Track background processes
- Display CPU and memory usage
- Add process sorting
- Add process priority management
- Improve command parsing
- Add process tree visualization

## License

This project is open source and available for learning and educational purposes.