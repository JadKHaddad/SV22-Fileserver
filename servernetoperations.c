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

#include "fileprotocol.h"
#include "fileoperations.h"
#include "servernetoperations.h"


/* Sendet *len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurück,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben.
   Implementieren Sie partielles senden (siehe Übung 2). */
int sendMsg(int sock, char *msg, int *len) {
    return -1;
} 

/* Erzeugen, binden und listen des server Sockets.
   Es soll ein IPv4 TCP Socket erzeugt werden. Dieser soll an jeder 
   Adresse des Hosts auf dem übergebenen Port svport lauschen.
   Der erzeugte und gebundene Socket soll über das Zeiger-Argument 
   listensocket zurückgeliefert werden.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int create_listensocket(int *listensocket, int svport) {
  return -1;
}


/* Empfangen eines clientrequest.
   Ueber den Socket sock einen clientrequest empfangen.
   Achten Sie dabei darauf alle nötigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_clientrequest(int sock, clientrequest *req) {
  return -1;  
}

/* Senden eines serverresponse und der datei.
   Zunächst den serverresponse über socket senden.
   Achten Sie dabei darauf alle nötigen Daten zu senden (sendMsg)
   und ggf. die byte-order umzudrehen.
   Falls eine Datei übergeben wurde (filebuffer != NULL, 
   resp.filelen > 0) soll anschließend der Inhalt dieses Puffers 
   vollständig gesendet werden. Verwenden sie dazu die Funktion sendMsg.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int send_response_and_file(int socket, serverresponse resp, char *filebuffer) {
    return -1;
}


/* Eine eingehen Verbindung akzeptieren und den neuen Socket zurückliefern.
 */
int accept_client(int listensocket) {
  return -1;
}


