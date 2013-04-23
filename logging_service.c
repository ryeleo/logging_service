/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/
#include <string.h>

/******************************************************************************/
/* Public facing API functions */
/******************************************************************************/
int print_to_log(char *message, int log){
    int ret;

    // write the message into log's memory buffer
    ret = strncat(LogService.log_buffers[log_index(log)], message, 
        MAX_BUFFER_SIZE-strlen(LogService.log_buffers[log_index(log)]));
    if (ret == -1)
        return -1;
    LogService.log_buffers[log_index(log)][MAX_BUFFER_SIZE-1] = '\0';

    // indicate using bitfield that this log needs to have its buffer flushed
    active_buffer = log | active_buffer;
}

int close_log(int log){
    // indicate using bitfield that this log needs to be closed
    active_close = log | active_close;
}

int open_log(char *file_name){
    int log;

    // cycle through each possible log number to find an available log to use
    for (i=0x00000001 ; i < 0x80000000 ; i << 1) {
        if (i & active_logs == 0)
            break;
    }
    if (i > 0x80000000) // all logs are actively being used
        return -1;
    log = i;
    
    // write the filename into log's filename buffer
    ret = strncpy(LogService.log_filenames[log_index(log)], file_name, MAX_STRLEN_FILENAME);
    if (ret == -1)
        return -1;
    LogService.log_filenamess[log_index(log)][MAX_STRLEN_FILENAME-1] = '\0';

    // indicate using bitfield that this log needs to be opened
    active_open = i | active_open;
}



/******************************************************************************/
/* Backend functions */
/******************************************************************************/
int s_print_to_log(int log){
    // XXX TODO write buffer to log file

    // indicate using bitfields that the log is no longer active
    active_buffer = active_buffer & (~log);
}

int s_close_log(int log){

    // XXX TODO Close the log file

    // indicate with bitfield that this operation has completed
    active_close = active_close & (~log);
    active_logs = active_logs & (~log);
}

int s_open_log(int log){

    // XXX TODO Open the log file

    // indicate with bitfield that this operation has completed
    active_open = active_open & (~log);
    active_logs = active_logs | log;
}

int init_logging_service(){
    // XXX TODO Allocate space for all buffers ahead of time
}

int exit_logging_service(){
    // XXX TODO Free all space from buffers
}

int log_index(int log){
    int i;
    for (i = 1 ; i < 32 ; i++)
        if (log & (1 << i) != 0)
            break;

    if (i < 32)
        return i;
    else 
        return -1;
}

#include "logging_service.h"
