/* request.c: Make HTTP Requests */

#include "request.h"

#include "macros.h"
#include "socket.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/* Constants */

#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'

/* Functions */

/**
 * Construct Request structure by parsing URL string into separate host, port,
 * and path components.
 *
 * @param   url         URL string to parse.
 *
 * @return  Request structure.
 **/
Request *   request_create(const char *url) {
    
    /* TODO: Copy data to local buffer */
    char buff[BUFSIZ];
    if (strcpy(buff, url) == NULL) return NULL;

    /* TODO: Skip scheme to host */

    char *host = strstr(buff, HOST_DELIMITER);
    
    if (!host) {
        host = buff;
    } else {
        *host = 0;
        host += 3;
    }

    /* TODO: Split host:port from path */
    char *path = strchr(host, PATH_DELIMITER);
    if (!path) {
        path = "";
    } else {
        *path = 0;
        path++;
    }

    /* TODO: Split host and port */
    char *port = strchr(host, PORT_DELIMITER);
    if (!port) {
        port = "80";
    } else {
        *port = 0;
        port++;
    }

    /* TODO: Allocate Request structure */
    Request *rs = malloc(sizeof(Request));
    rs->host = malloc(BUFSIZ);
    rs->port = malloc(BUFSIZ);
    rs->path = malloc(BUFSIZ);

    /* TODO: Copy components to URL structure */
    strcpy(rs->host, host);
    strcpy(rs->port, port);
    strcpy(rs->path, path);

    return rs;
}

/**
 * Deallocate Request structure.
 *
 * @param   request     Request structure to deallocate.
 **/
void	    request_delete(Request *request) {
    free(request->host);
    free(request->port);
    free(request->path);
    free(request);
}

/**
 * Make a HTTP request and write the contents of the response to the specified
 * stream.
 *
 * @param   url         Make a HTTP request to this URL.
 * @param   stream      Write the contents of response to this stream.
 *
 * @return  -1 on error, otherwise the number of bytes written.
 **/
ssize_t     request_stream(Request *request, FILE *stream) {
    /* TODO: Connect to remote host and port */
    FILE *client_file = socket_dial(request->host, request->port);
    if (!client_file) return -1;

    /* TODO: Send request to server */
    fprintf(client_file, "GET /%s HTTP/1.0\r\n", request->path);
    fprintf(client_file, "Host: %s\r\n", request->host);
    fprintf(client_file, "\r\n"); 

    /* TODO: Read response status from server */
    char buffer[BUFSIZ];
    fgets(buffer, BUFSIZ, client_file);
    if (!strstr(buffer,"200 OK")) {
        fprintf(stderr, "Unsuccessful Response\n");
        return -1;
    }

    /* TODO: Read response headers from server */
    size_t content_length = 0;
    while(fgets(buffer, BUFSIZ, client_file) && strcmp(buffer, "\r\n")) {
        sscanf(buffer, "Content-Length: %lu", &content_length);
    }

    /* TODO: Read response body from server */
    size_t bytes_written = 0;
    size_t bytes_read;

    do {
        bytes_read = fread(buffer, 1, BUFSIZ, client_file);
        bytes_written += fwrite(buffer, 1, bytes_read, stream);
    } while (content_length != 0 && bytes_written < content_length);

    /* TODO: Close connection */
    fclose(client_file);

    /* TODO: Return number of bytes written and check if it matches Content-Length */
    if (bytes_written != content_length && content_length != 0)
        return -1;

    return bytes_written;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
