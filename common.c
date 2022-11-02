#include "common.h"


void err(char *msg) {
    perror(msg);
    exit (EXIT_FAILURE);
}

