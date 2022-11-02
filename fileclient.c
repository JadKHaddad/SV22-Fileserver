#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "fileprotocol.h"
#include "clientnetoperations.h"

/* Überprüfen und Auslesen der Kommandozeilenparameter,
   setzt globale Variable svport */
int extractArgs(int argc, char **argv, short *svport)
{
  if (argc != 4) {
    fprintf(stderr, "Usage: %s host port filename\n", argv[0]);
    return -1;
  }
  if(strlen(argv[3]) > FP_MAXFILENAME)
  {
    fprintf (stderr, "Filename too long\n");
    return -1;
  }
  *svport = (short)atoi(argv[2]);
  return 0;
}

int main(int argc, char **argv) {
  int sock;
  short svport;
  clientrequest req;
  serverresponse resp;


  /* Argumente auslesen */
  if (extractArgs(argc, argv, &svport)) {
    fprintf(stderr, "Error while processing arguments\n");
    return EXIT_FAILURE;
  }

  /* socket zum server verbinden */
  if(connect_server(&sock, argv[1], svport)) {
    fprintf(stderr, "Error during connect\n");
    return EXIT_FAILURE;
  }

  /* Request initialisieren */
  req.cmd = FP_GET;
  strncpy(req.filename, argv[3], FP_MAXFILENAME);



  /* Request an Server senden */
  if(send_request(sock, &req)) {
    fprintf(stderr, "Error during sending of request\n");
    close(sock);
    return EXIT_FAILURE;
  }

  /* Antwort vom Server empfangen */
  if(recv_reply(sock,&resp)) {
    fprintf(stderr, "Error during receiving of reply\n");
    close(sock);
    return EXIT_FAILURE;
  }

  /* Antwort vom Server prüfen und verarbeiten */
  if(resp.retcode == FP_BADREQUEST)
    err("Server responded: FP_BADREQUEST\n");
  if(resp.retcode == FP_FILENOTFOUND)
    err("Server responded: FP_FILENOTFOUND\n");
  if(resp.retcode == FP_GENERROR)
    err("Server responded: FP_GENERROR\n");

  /* Falls Antwort OK: Datei empfangen und ausgeben */
  if(resp.retcode == FP_OK) {
    if(recv_and_print_file(sock,resp.filelen) < 0) {
      fprintf(stderr, "Error during receiving of file\n");
      close(sock);
      return EXIT_FAILURE;
    }
  }

  /* Verbindung beenden und socket freigeben */
  close(sock);
  
  /* Ende von main */
  return EXIT_SUCCESS;
}
