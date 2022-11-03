#ifndef COMMON_INC
#define COMMON_INC

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

void err(char *msg);

/* Sendet &len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben */
int sendMsg(int sock, char *msg, int *len);

#endif
