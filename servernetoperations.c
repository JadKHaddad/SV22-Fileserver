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

/* Erzeugen, binden und listen des server Sockets.
   Es soll ein IPv4 TCP Socket erzeugt werden. Dieser soll an jeder
   Adresse des Hosts auf dem uebergebenen Port svport lauschen.
   Der erzeugte und gebundene Socket soll ueber das Zeiger-Argument
   listensocket zurueckgeliefert werden.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int create_listensocket(int *listensocket, int svport)
{
  struct sockaddr_in my_addr;

  *listensocket = socket(AF_INET, SOCK_STREAM, 0);
  if (*listensocket == -1)
  {
    perror("socket");
    return -1;
  }

  memset(&my_addr, 0, sizeof(struct sockaddr_in));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr.sin_port = htons(svport);

  if (bind(*listensocket, (struct sockaddr *)&my_addr,
           sizeof(my_addr)) == -1)
  {
    close(*listensocket);
    perror("bind");
    return -1;
  }
  if (listen(*listensocket, LISTENBACKLOG) == -1)
  {
    close(*listensocket);
    perror("listen");
    return -1;
  }
  return 0;
}

/* Empfangen eines clientrequest.
   Ueber den Socket sock einen clientrequest empfangen.
   Achten Sie dabei darauf alle noetigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_clientrequest(int sock, clientrequest *req)
{
  int bytesrcvd = recv(sock, (void *)req, sizeof(clientrequest), 0);
  if (bytesrcvd <= 0)
  {
    perror("recv");
    return -1;
  }
  req->cmd = ntohl(req->cmd); /*host byte order*/
  return 0;
}

/* Senden eines serverresponse und der datei.
   Zunaechst den serverresponse ueber socket senden.
   Achten Sie dabei darauf alle noetigen Daten zu senden (sendMsg)
   und ggf. die byte-order umzudrehen.
   Falls eine Datei uebergeben wurde (filebuffer != NULL,
   resp.filelen > 0) soll anschliessend der Inhalt dieses Puffers
   vollstaendig gesendet werden. Verwenden sie dazu die Funktion sendMsg.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int send_response_and_file(int socket, serverresponse resp, char *filebuffer)
{
  int size = sizeof(resp), retval, filelen = resp.filelen;

  /* byte-order beachten */
  resp.retcode = htonl(resp.retcode); /*network byte order*/
  resp.filelen = htonl(resp.filelen); /*network byte order*/

  /* response senden */
  retval = sendMsg(socket, (char *)&resp, &size);
  if (size != sizeof(resp))
  {
    perror("send");
    return -1;
  }

  /* Datei senden, falls vorhanden und L�nge != 0 */
  size = filelen;
  if (size != 0 && file != NULL && retval != -1)
  {
    retval = sendMsg(socket, (char *)file, &size);
    if (size != filelen)
    {
      perror("send");
      return -1;
    }
  }
  return 0;
}

/* Eine eingehen Verbindung akzeptieren und den neuen Socket zurueckliefern.
 */
int accept_client(int listensocket)
{
  int cfd;
  struct sockaddr_in peer_addr;
  socklen_t peer_addr_size;
  peer_addr_size = sizeof(peer_addr);

  cfd = accept(listensocket, (struct sockaddr *)&peer_addr,
               &peer_addr_size);
  if (cfd == -1)
  {
    close(listensocket);
    perror("accept");
    return -1;
  }
  return cfd;
}
