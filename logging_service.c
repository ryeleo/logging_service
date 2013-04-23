/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/
#include <string.h>
#include "logging_service.h"

/******************************************************************************/
/* Public facing API functions */
/******************************************************************************/
void print_to_log(char *message, int log){
    // write the message into log's memory buffer
    strncat(LoggingService.log_buffers[log_index(log)], message,
        MAX_BUFFER_SIZE-strlen(LoggingService.log_buffers[log_index(log)]));
    LoggingService.log_buffers[log_index(log)][MAX_BUFFER_SIZE-1] = '\0';

    // indicate using bitfield that this log needs to have its buffer flushed
    LoggingService.active_buffer = log | LoggingService.active_buffer;
}

void close_log(int log){
    // indicate using bitfield that this log needs to be closed
    LoggingService.active_close = log | LoggingService.active_close;
}

int open_log(char *file_name){
    int log, i;

    // cycle through each possible log number to find an available log to use
    for (i=0x00000001 ; i < 0x80000000 ; i=i<<1) {
        if (( i & LoggingService.active_logs) == 0)
            break;
    }
    if (i > 0x80000000) // all logs are actively being used
        return -1;
    log = i;
    
    // write the filename into log's filename buffer
    strncpy(LoggingService.log_filenames[log_index(log)], file_name, MAX_STRLEN_FILENAME);
    LoggingService.log_filenames[log_index(log)][MAX_STRLEN_FILENAME-1] = '\0';

    // indicate using bitfield that this log needs to be opened
    LoggingService.active_open = i | LoggingService.active_open;

    return 0;
}



/******************************************************************************/
/* Backend functions */
/******************************************************************************/
int s_print_to_log(int log){
    // XXX TODO write buffer to log file

    // indicate using bitfields that the log is no longer active
    LoggingService.active_buffer = (LoggingService.active_buffer & (~log));
    
    return 0;
}

int s_close_log(int log){

    // XXX TODO Close the log file

    // indicate with bitfield that this operation has completed
    LoggingService.active_close = (LoggingService.active_close & (~log));
    LoggingService.active_logs = (LoggingService.active_logs & (~log));

    return 0;
}

int s_open_log(int log){

    // XXX TODO Open the log file

    // indicate with bitfield that this operation has completed
    LoggingService.active_open = (LoggingService.active_open & (~log));
    LoggingService.active_logs = LoggingService.active_logs | log;

    return 0;
}

int init_logging_service(){
    // XXX TODO Allocate space for all buffers ahead of time
    return 0;
}

int exit_logging_service(){
    // XXX TODO Free all space from buffers
    return 0;
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

#include "logging_service.h"
