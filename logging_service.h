/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/

#ifndef __LOGGING_SERVICE_H__
#define __LOGGING_SERVICE_H__
#define LOGGING_EXE "./logging_service"
#define MAX_STRLEN_FILENAME 512
#define MAX_BUFFER_SIZE 4056
#define MAX_ACTIVE_LOGS sizeof(int)*8

struct Log{
};

struct LoggingService{
    // bitfield
    int active_logs;                        // A bit array of the active logs
    //int active_buffer;                      // A bit array indicating that a buffer is active
    //int active_open;                        // A bit array indicating that a log needs to be opened
    //int active_close;                       // A bit array indicating that a log needs to be closed

    // variables needed for implementation
    int   log_fds[MAX_ACTIVE_LOGS];         // The file descriptors associated with each open log
    char *log_filenames[MAX_ACTIVE_LOGS];   // The filename associated with each open log
    char *log_buffers[MAX_ACTIVE_LOGS];     // The buffer associated with each open log
} LoggingService;

/******************************************************************************/
/* Backend functions */
/******************************************************************************/
int s_print_to_log(char *message, int log);
int s_close_log(int log);
int s_open_log(char *fname);
int init_logging_service();
void exit_logging_service();
int log_index(int log);

#endif/*__LOGGING_SERVICE_H__*/
