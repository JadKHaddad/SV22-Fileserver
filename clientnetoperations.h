#ifndef CLIENTNETOPERATIONS_INC
#define CLIENTNETOPERATIONS_INC

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "fileprotocol.h"

/* Sendet &len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben */
int sendMsg(int sock, char *msg, int *len);

/* Verbindung zum Server auf sock herstellen */
int connect_server(int *sock, char *hostname, short svport);

/* Request an Server ueber sock senden */
int send_request(int sock, clientrequest *req);

/* Reply ueber sock vom Server empfangen */
int recv_reply(int sock, serverresponse *resp);

/* Datei ueber sock empfangen und ausgeben. */
int recv_and_print_file(int sock, int filelen);


#endif
