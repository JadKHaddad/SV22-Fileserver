#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "fileprotocol.h"
#include "clientnetoperations.h"

#define BUFSIZE 512

/* Sendet *len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurück,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben.
   Implementieren Sie partielles senden (siehe Übung 2). */
int sendMsg(int sock, char *msg, int *len)
{
  return -1;
}

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
   Achten Sie dabei darauf alle nötigen Daten zu senden (sendMsg)
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck
*/
int send_request(int sock, clientrequest *req)
{
  return -1;
}

/* Datei über socket empfangen und ausgeben.
   Im Falle eines erfolgreichen serverresponse wird anschließend die
   Datei (von der Größe filelen) empfangen. Die Daten der Datei sollen
   ausgegeben (fprintf(stdout, ... ), bzw. printf) werden.
   Achten sie darauf alle daten zu empfangen (partielles empfangen)!
 */
int recv_and_print_file(int sock, int filelen)
{
  return -1;
}

/* Ueber den Socket sock einen serverresponse empfangen.
   Achten Sie dabei darauf alle nötigen Daten zu empfangen
   und ggf. die byte-order umzudrehen.
   Gibt -1 bei Fehler und 0 bei Erfolg zurueck */
int recv_reply(int sock, serverresponse *resp)
{
  return -1;
}
