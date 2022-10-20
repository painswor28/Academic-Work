/* hammer.c: Make HTTP request and measure bandwidth */

#include "hammer.h"
#include "macros.h"
#include "request.h"
#include "timestamp.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Constants */

#define MEGABYTE    (double)(1<<20)

/* Functions */

/**
 * Perform a hammer through by making a HTTP request to the specified URL and
 * printing the contents of the response to the given stream.
 * Function prints the bandwidth of the HTTP transaction if it is successful to
 * stderr.
 *
 * @param   url         Make HTTP request to this URL.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not the HTTP request was successful.
 **/
bool	hammer(const char *url, FILE *stream) {
    /* TODO: Perform HTTP request */
    Request *request = request_create(url);
    
    double start_time = timestamp();
    ssize_t bytes_written = request_stream(request, stream);
    request_delete(request);
    double end_time = timestamp();

    /* TODO: Compute and display bandwith to stderr if HTTP request was
     * successful */
    double bandwidth = bytes_written / 1048576.0 / (end_time - start_time);
    if (bandwidth < 0)
        return false; 

    fprintf(stderr, "Bandwidth: %0.2lf MB/s\n", bandwidth);

    return true;
}

/**
 * Make hammers HTTP requests to the specified url, while writing the contents
 * of the request to the specified stream.
 *
 * Each HTTP request must be performed by a separate child process.
 *
 * Function prints the total elapsed time for all throws to stderr at the end.
 *
 * @param   url         Make HTTP requests to this URL.
 * @param   hammers     The number of HTTP requests to make.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not all hammer throws were successful.
 **/
bool	throw(const char *url, size_t hammers, FILE *stream) {
    double start_time = timestamp();
    /* TODO: Throw all hammers by spawning child processes that call hammer and
     * exit success if the hammer throw was successful. */
    bool throw_success;
    pid_t pids[hammers];
    
    for (int i = 0; i < hammers; i++) {
        if ((pids[i] = fork()) < 0) {
            return false;
        } else if (pids[i] == 0) {
            throw_success = hammer(url, stream);
            exit(throw_success);
        }
    }

    /* TODO: Collect results of throws by waiting for all children */
    int status = EXIT_SUCCESS;
    bool success = true;
    for (int i = 0; i < hammers; i++) {
        wait(&status);
        if (status == 0) success = false;
    }

    /* TODO: Print elapsed time to stderr */
    if (success) {
        double end_time = timestamp();
        fprintf(stderr, "Elapsed Time: %0.2lf seconds\n", end_time - start_time);
    }
    return success;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
