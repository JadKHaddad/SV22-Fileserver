#ifndef SERVERNETOPERATIONS_INC
#define SERVERNETOPERATIONS_INC

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

#include "common.h"

#define MAXMSG 512
#define LISTENBACKLOG 1

/* Sendet &len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben */
int sendMsg(int sock, char *msg, int *len);


/* Erzeugen, binden und listen von listensocket,
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int create_listensocket(int *listensocket,int svport);


/* Erzeugen, binden und listen von listensocket,
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_clientrequest(int sock, clientrequest *req);


int send_response_and_file(int socket, serverresponse resp, char *filebuffer);


int accept_client(int listensocket);

#endif
