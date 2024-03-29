/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "logging_service.h"


int s_print_to_log(char *message, int log){
    int ret;

    // print message to log file
    ret = write(LoggingService.log_fds[log_index(log)], 
        LoggingService.log_buffers[log_index(log)], 
        strlen(LoggingService.log_buffers[log_index(log)]));
    if (ret == -1)
        ret = -1;
    else
        ret = 0;

    // indicate using bitfields that the log is no longer active
    LoggingService.active_buffer = (LoggingService.active_buffer & (~log));
    
    return ret;
}

int s_close_log(int log){
    int ret;

    // Close log file
    ret = close(LoggingService.log_fds[log_index(log)]);
    if (ret == -1)
        ret = -1;
    else 
        ret = 0;

    // indicate with bitfield that this operation has completed
    LoggingService.active_close = (LoggingService.active_close & (~log));
    LoggingService.active_logs = (LoggingService.active_logs & (~log));

    return ret;
}

int s_open_log(char *fname){
    int ret;

    // open fname
    ret = open(LoggingService.log_filenames[log_index(log)], O_RDWR | O_APPEND | O_CREAT, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ret == -1)
        ret = -1;
    else{
        LoggingService.log_fds[log_index(log)] = ret;
        ret = 0;
        LoggingService.active_logs = LoggingService.active_logs | log;
    }

    // indicate with bitfield that this operation has completed
    LoggingService.active_open = (LoggingService.active_open & (~log));

    return ret;
}

int init_logging_service(){
    int i;    

    for (i = 0 ; i < MAX_ACTIVE_LOGS-1 ; i++){ // allocate space for all 31 logs
        LoggingService.log_filenames[log_index(i)] = malloc(MAX_STRLEN_FILENAME * sizeof(char));
        LoggingService.log_buffers[log_index(i)] = malloc(MAX_BUFFER_SIZE * sizeof(char));
        if ( LoggingService.log_filenames[log_index(i)] == NULL)
            return -1;
        if ( LoggingService.log_buffers[log_index(i)] == NULL)
            return -1;
    }
    
    return 0;
}

void exit_logging_service(){
    int i;
    for (i = 0 ; i < MAX_ACTIVE_LOGS-1 ; i++){ // free all space from the 31 logs
        free(LoggingService.log_filenames[log_index(i)]);
        free(LoggingService.log_buffers[log_index(i)]);
    }
}

int log_index(int log){
    int i;
    for (i = 1 ; i < 32 ; i++)
        if ((log & (1<<i)) != 0)
            break;

    if (i < 32)
        return i;
    else 
        return -1;
}
