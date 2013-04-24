/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logging_service.h"

#define BUFFER_P    0
#define FNAME_P     1
#define A_CLOSE_P   2
#define A_BUFFER_P  3
#define ERROR_P     4

int run_backend();


int main(int argc, char **argv){
    int pipes[5];
    pipes = (int*) argv;
    ret = run_backend(pipes);
    if (ret == -1) {
        printf("Error running logging_service daemon");
        exit(-1);
    }

    // This code is never reached
    exit(0);

} // END main


int run_backend(int *pipes){
    int i, ret, log_d;    
    char message[MAX_BUFFER_SIZE];

    while (1) {
        // Have to wait here to see if there is any incoming garbage from pipes
        // using a call to select.
        ret = select();
        if (ret == -1)
            return -1;

        switch () {

            case pipes[FNAME_P]:
                s_open_log();
                break;

            case pipes[A_CLOSE_P]:
                s_close_log(log_d);
                break;

            case pipes[A_BUFFER_P]:
                s_print_to_log(message, log_d);
                break;

            case pipes[BUFFER_P]:
                s_close_log();
                break;

            default:
                return -1;
                break;
        }

        
        /*
        // cycle through each log
        for (i=0x00000001 ; i < 0x80000000 ; i = i << 1) {
            
            // check if log i needs to be opened
            if ((LoggingService.active_open & i) != 0) { // there is content to be written
                ret = s_open_log(i);
                if (ret == -1)
                    printf("Unable to open log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }
            
            // check if log i has any buffered content that needs to be written to file
            if ((LoggingService.active_buffer & i) != 0) { // there is content to be written
                ret = s_print_to_log(i);
                if (ret == -1)
                    printf("Unable to write to log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }

            // check if log i needs to be closed
            if ((LoggingService.active_close & i) != 0) { // there is content to be written
                ret = s_close_log(i);
                if (ret == -1)
                    printf("Unable to close log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }
        }
        */
    }
}



static void usage(char **argv)
{
    printf("Usage: ");
    if (argv != NULL && argv[0] != NULL)
        printf("%s [-s]\n", argv[0]);
    else
        printf("logging_service [-s]\n");
}
