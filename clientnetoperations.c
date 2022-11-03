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
  int len = (int)sizeof(clientrequest);
  return sendMsg(sock, (void *)req, &len);
}

/* Datei über socket empfangen und ausgeben.
   Im Falle eines erfolgreichen serverresponse wird anschließend die
   Datei (von der Größe filelen) empfangen. Die Daten der Datei sollen
   ausgegeben (fprintf(stdout, ... ), bzw. printf) werden.
   Achten sie darauf alle daten zu empfangen (partielles empfangen)!
 */
int recv_and_print_file(int sock, int filelen)
{
  char buf[BUFSIZE];
  int rec = recv(sock, buf, BUFSIZE - 1, filelen);
  if (rec == -1)
  {
    perror("recv");
    return -1;
  }
  buf[rec] = '\0';
  printf("%s\n", buf);
  fflush(stdout);
  return 0;
}

/* Ueber den Socket sock einen serverresponse empfangen.
   Achten Sie dabei darauf alle nötigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_reply(int sock, serverresponse *resp)
{
  int bytesrcvd = recv(sock, (void *)resp, sizeof(serverresponse), 0);
  if (bytesrcvd < 0)
  {
    perror("recv");
    return -1;
  }
  return 0;
}
