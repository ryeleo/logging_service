/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logging_service.h"

/*
*/
int run_backend();
static void usage(char **argv);

char silent_mode = 'N';

int main(int argc, char **argv){
    int ret;

    // parse options at command line
    while ((ret = getopt(argc, argv, "s")) != -1)
    {
        switch (ret)
        {
            case 's':
                silent_mode = 'Y';
                break;
            default:
                usage(argv);
                exit(0);
        }
    }


    // startup as daemon
    ret = fork();
    if (ret > 0) { // if we are the parent
        exit(0); 
    } else if (ret < 0) { // if there was an error
        printf("Error deamonizing logging_service");
        exit(-1); 
    }   
    ret = run_backend();
    if (ret == -1) {
        printf("Error running logging_service daemon");
        exit(-1);
    }

    // This code is never reached
    exit(0);

} // END main


int run_backend(){
    int i,      // the log iterator
        ret;    
    char *log_buffer;
    while (1) {

        // cycle through each log
        for (i=0x00000001 ; i < 0x80000000 ; i << 1) {
            
            // check if log i needs to be opened
            if (active_open & i != 0) { // there is content to be written
                ret = s_open_log(i);
                if (ret == -1 && silent_mode != 'Y')
                    printf("Unable to open log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }
            
            // check if log i has any buffered content that needs to be written to file
            if (active_buffer & i != 0) { // there is content to be written
                ret = s_print_to_log(i);
                if (ret == -1 && silent_mode != 'Y')
                    printf("Unable to write to log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }

            // check if log i needs to be closed
            if (active_close & i != 0) { // there is content to be written
                ret = s_close_log(i);
                if (ret == -1 && silent_mode != 'Y')
                    printf("Unable to close log: %d:%s", 
                        log_index(i), LoggingService.log_filenames[log_index(i)]);
            }
        }
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
