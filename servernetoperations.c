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
   Gibt -1 bei Fehler und 0 bei Erfolg zur�ck,
   Tats�chliche Anzahl gesendeter Bytes wird in len geschrieben.
   Implementieren Sie partielles senden (siehe �bung 2). */
int sendMsg(int sock, char *msg, int *len)
{
  return -1;
}

/* Erzeugen, binden und listen des server Sockets.
   Es soll ein IPv4 TCP Socket erzeugt werden. Dieser soll an jeder
   Adresse des Hosts auf dem uebergebenen Port svport lauschen.
   Der erzeugte und gebundene Socket soll ueber das Zeiger-Argument
   listensocket zurueckgeliefert werden.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int create_listensocket(int *listensocket, int svport)
{

  char svport_str[20];
  sprintf(svport_str, "%d", svport);

  *listensocket = socket(AF_INET, SOCK_STREAM, 0);
  if (*listensocket == -1)
  {
    perror("socket");
    return -1;
  }

  struct sockaddr_in my_addr;

  memset(&my_addr, 0, sizeof(struct sockaddr_in));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr.sin_port = htons(svport);

  if (bind(*listensocket, (struct sockaddr *)&my_addr,
           sizeof(my_addr)) == -1)
  {
    perror("bind");
    return -1;
  }
  if (listen(*listensocket, 50) == -1)
  {
    perror("listen");
    return -1;
  }
  return 0;
}

/* Empfangen eines clientrequest.
   Ueber den Socket sock einen clientrequest empfangen.
   Achten Sie dabei darauf alle n�tigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_clientrequest(int sock, clientrequest *req)
{
  return -1;
}

/* Senden eines serverresponse und der datei.
   Zun�chst den serverresponse �ber socket senden.
   Achten Sie dabei darauf alle n�tigen Daten zu senden (sendMsg)
   und ggf. die byte-order umzudrehen.
   Falls eine Datei �bergeben wurde (filebuffer != NULL,
   resp.filelen > 0) soll anschlie�end der Inhalt dieses Puffers
   vollst�ndig gesendet werden. Verwenden sie dazu die Funktion sendMsg.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int send_response_and_file(int socket, serverresponse resp, char *filebuffer)
{
  return -1;
}

/* Eine eingehen Verbindung akzeptieren und den neuen Socket zurueckliefern.
 */
int accept_client(int listensocket)
{
  printf("Accepting clients\n");
  fflush(stdout);

  int cfd;
  struct sockaddr_in peer_addr;
  socklen_t peer_addr_size;
  peer_addr_size = sizeof(peer_addr);

  cfd = accept(listensocket, (struct sockaddr *)&peer_addr,
               &peer_addr_size);
  if (cfd == -1)
  {
    printf("Accepting clients failed\n");
    fflush(stdout);
    perror("accept");
    return -1;
  }
  return cfd;
}
