#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "fileprotocol.h"
#include "clientnetoperations.h"

#define BUFSIZE 512

/* Verbindung zum Server auf sock herstellen.
   Zunächst muss ein Socket erstellt werden (IPv4 TCP) und die Adresse
   des Server aufgelöst werden (hostname+svport).
   Der erzeugte socket soll zum Server verbunden werden und über das
   Zeiger-Argument sock zurückgeliefert werden.
   Gibt -1 bei Fehler und 0 bei Erfolg zurück,
*/
int connect_server(int *sock, char *hostname, short svport)
{
  struct sockaddr_in server_addr;

  *sock = socket(AF_INET, SOCK_STREAM, 0);
  if (*sock == -1)
  {
    perror("socket");
    return -1;
  }

  memset(&server_addr, 0, sizeof(struct sockaddr_in));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(hostname);
  server_addr.sin_port = htons(svport);

  if (connect(*sock, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) == -1)
  {
    perror("connect");
    return -1;
  }
  return 0;
}

/* Den übergebenen clientrequest über den socket senden.
   Achten Sie dabei darauf alle noetigen Daten zu senden (sendMsg)
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck
*/
int send_request(int sock, clientrequest *req)
{
  int retval, send_msg_size;

  req->reqlen = htonl(req->reqlen); /*network byte order*/
  req->cmd = htonl(req->cmd);       /*network byte order*/
  /* Nachricht senden */
  send_msg_size = sizeof(clientrequest);
  retval = sendMsg(sock, (char *)req, &send_msg_size);
  if (send_msg_size != sizeof(clientrequest))
  {
    perror("send");
    return -1;
  }
  return 0;
}

/* Datei über socket empfangen und ausgeben.
   Im Falle eines erfolgreichen serverresponse wird anschließend die
   Datei (von der Größe filelen) empfangen. Die Daten der Datei sollen
   ausgegeben (fprintf(stdout, ... ), bzw. printf) werden.
   Achten sie darauf alle daten zu empfangen (partielles empfangen)!
 */
int recv_and_print_file(int sock, int filelen)
{
  int filerecvd = 0, bytesrcvd = 0;
  char buffer[BUFSIZE];

  while (filerecvd < filelen)
  {
    bytesrcvd = recv(sock, buffer, BUFSIZE - 1, 0);
    if (bytesrcvd <= 0)
    {
      perror("recv");
      return -1;
    }
    buffer[bytesrcvd] = '\0';
    fprintf(stdout, "%s", buffer);
    filerecvd += bytesrcvd;
  }
  return 0;
}

/* Ueber den Socket sock einen serverresponse empfangen.
   Achten Sie dabei darauf alle nötigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_reply(int sock, serverresponse *resp)
{
  int bytesrcvd = 0, rcvd = 0;

  /* Antwort empfangen */
  while (bytesrcvd < sizeof(serverresponse))
  {
    rcvd = recv(sock, ((char *)resp) + bytesrcvd,
                sizeof(serverresponse) - bytesrcvd, 0);
    if (rcvd <= 0)
    {
      perror("recv");
      return -1;
    }
    bytesrcvd += rcvd;
  }
  resp->retcode = ntohl(resp->retcode); /* host byte order */
  resp->filelen = ntohl(resp->filelen); /* host byte order */
  return 0;
}
