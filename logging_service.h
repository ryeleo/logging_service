/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
*/

#ifndef __LOGGING_SERVICE_H__
#define __LOGGING_SERVICE_H__
#define MAX_STRLEN_FILENAME 512
#define MAX_BUFFER_SIZE 4056
#define MAX_ACTIVE_LOGS sizeof(int)*8

struct Log{
};

struct LoggingService{
    int active_logs;                        // A bit array of the active logs
    char *log_filenames[MAX_ACTIVE_LOGS];   // The filename associated with each open log
    char *log_buffers[MAX_ACTIVE_LOGS];     // The buffer associated with each open log
} LoggingService;

/******************************************************************************/
/* Public facing API functions */
/******************************************************************************/
int print_to_log(char *message, int log);
int close_log(int log);
int open_log(char *file_name);



/******************************************************************************/
/* Backend functions */
/******************************************************************************/
int s_print_to_log(char *message, int log);
int s_close_log(int log);
int s_open_log(char *file_name);
int init_logging_service();
int exit_logging_service();

#endif/*__LOGGING_SERVICE_H__*/
