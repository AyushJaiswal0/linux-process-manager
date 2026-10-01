#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main(void)
{
    int choice;
    char input[32];

    while (1)
    {
        printf("\n===== Linux Process Manager =====\n");
        printf("1. List Processes\n");
        printf("2. Search Process\n");
        printf("3. Process Information\n");
        printf("4. Start Process\n");
        printf("5. Terminate Process\n");
        printf("6. Pause Process\n");
        printf("7. Resume Process\n");
        printf("8. Exit\n");
        printf("Enter choice: ");

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;
        
        char *end;
        choice = strtol(input, &end, 10);

        if(end == input)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                list_processes();
                break;

            case 2:
                search_process();
                break;

            case 3:
                process_info();
                break;

            case 4:
                start_process();
                break;

            case 5:
                terminate_process();
                break;

            case 6:
                pause_process();
                break;
            
            case 7:
                resume_process();
                break;

            case 8:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please select 1-8.\n");
        }
    }

    return 0;
}