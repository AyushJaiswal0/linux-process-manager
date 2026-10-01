#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "process.h"

int get_pid_input(void)
{
    char input[32];
    char *end;
    long pid;

    printf("Enter PID: ");

    if(fgets(input, sizeof(input), stdin) == NULL)
        return -1;
    
    pid = strtol(input, &end, 10);

    if(end == input || pid <=0 || pid > 2147483647)
    {
        printf("Invalid PID.\n");
        return -1;
    }
    return (int)pid;
}

void list_processes(void)
{
    DIR *dir = opendir("/proc");

    if(dir == NULL)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    printf("\n%-10s %-30s\n", "PID", "PROCESS");
    printf("-------------------------------------------\n");

    while((entry = readdir(dir)) != NULL)
    {
        if(!isdigit((unsigned char)entry->d_name[0]))
            continue;

        char path[512];
        char name[256];

        snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
        FILE *file = fopen(path, "r");

        if(file == NULL)
            continue;
        if(fgets(name, sizeof(name), file) != NULL)
        {
            name[strcspn(name, "\n")] = '\0';
            printf("%-10s %-30s\n", entry->d_name, name);
        }
        fclose(file);
    }
    closedir(dir);
}

void search_process(void)
{
    char target[256];

    printf("Enter process name: ");

    if (fgets(target, sizeof(target), stdin) == NULL)
        return;

    target[strcspn(target, "\n")] = '\0';

    if (target[0] == '\0')
    {
        printf("Process name cannot be empty.\n");
        return;
    }

    DIR *dir = opendir("/proc");

    if(dir == NULL)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    int found = 0;
    printf("\n%-10s %-30s\n", "PID", "PROCESS");
    printf("--------------------------------------------\n");

     while((entry = readdir(dir)) != NULL)
    {
        if(!isdigit((unsigned char)entry->d_name[0]))
            continue;

        char path[512];
        char name[256];

        snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
        FILE *file = fopen(path, "r");

        if(file == NULL)
            continue;
        if(fgets(name, sizeof(name), file) != NULL)
        {
            name[strcspn(name, "\n")] = '\0';
            if(strcmp(name, target) == 0)
            {
                printf("%-10s %-30s\n", entry->d_name, name);
                found = 1;
            }
        }
        fclose(file);
    }
    closedir(dir);

    if(!found)
        printf("No process found with name: %s\n", target);
}

void process_info(void)
{
    int pid = get_pid_input();
    if(pid == -1)
        return;
    char path[512];
    char line[256];

    snprintf(path, sizeof(path), "/proc/%d/status",pid);

    FILE *file = fopen(path, "r");

    if(file == NULL)
    {
        printf("Process with PID %d not found.\n", pid);
        return;
    }

    printf("\n===== Process Information =====\n");

    while(fgets(line, sizeof(line), file) != NULL)
    {
        if(strncmp(line, "Name:", 5) == 0 ||
           strncmp(line, "State:", 6) == 0 ||
           strncmp(line, "Pid:", 4) == 0 ||
           strncmp(line, "PPid:", 5) == 0 ||
           strncmp(line, "Threads:", 8) == 0)
        {
            printf("%s", line);
        }
    }
    fclose(file);
}

void start_process(void)
{
    char input[256];
    char *args[32];
    int count = 0;

    printf("Enter command: ");
    if(fgets(input, sizeof(input), stdin) == NULL)
        return; 

    input[strcspn(input, "\n")] = '\0';
    char *token = strtok(input, " ");
    while(token != NULL && count < 31)
    {
        args[count++] = token;
        token = strtok(NULL, " ");
    }

    args[count] = NULL;
    if(count==0)
    {
        return;
    }

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return;
    }

    if(pid == 0)
    {
        execvp(args[0], args);
        fprintf(stderr, "Failed to execute '%s': command not found.\n", args[0]);
        _exit(127);
    }

    printf("Process created with PID: %d\n", pid);
}

void terminate_process(void)
{
    int pid = get_pid_input();
    if(pid == -1)
        return;

    if(kill(pid, SIGTERM)==-1)
    {
        perror("kill");
        return;
    }

    printf("Termination signal sent to process %d.\n", pid);
}

void pause_process(void)
{
    int pid = get_pid_input();
    if(pid == -1)
        return;

    if(kill(pid, SIGSTOP)==-1)
    {
        perror("kill");
        return;
    }

    printf("Process %d paused.\n", pid);
}

void resume_process(void)
{
    int pid = get_pid_input();
    if(pid == -1)
        return;

    if(kill(pid, SIGCONT)==-1)
    {
        perror("kill");
        return;
    }

    printf("Process %d resumed.\n", pid);
}