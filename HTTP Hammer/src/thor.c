/* thor.c */

#include "hammer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] URL\n", progname);
    fprintf(stderr, "    -n HAMMERS How many times to hammer the URL\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    char * progname = argv[0];
    size_t argind = 1;
    size_t hammers = 1;

    if (argc < 2){
        usage(progname, 1);
    }
    while (argind < argc && argv[argind][0] == '-' && strlen(argv[argind]) > 1 ){
        switch (argv[argind][1]) {
            case 'h':
                usage(progname, 0);
                break;
            case 'n':
                argind++;
                hammers = atoi(argv[argind]);
                break;
            default:
                usage(progname, 1);
        }
        argind++;
    }

    const char *url = argv[argind];

    /* TODO: Throw Hammers */
    bool result = throw(url, hammers, stdout);

    return !result;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
