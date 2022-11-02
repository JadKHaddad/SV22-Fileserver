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
#include "common.h"

/* �berpr�fen und Auslesen der Kommandozeilenparameter,
   setzt globale Variable svport */
int extractArgs(int argc, char **argv, short* svport)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    return EXIT_FAILURE;
  }
  *svport = (short)atoi(argv[1]);
  return 0;
}

/* Verarbeitet einen FP_GET-request und sendet die Antwort */
int process_get_request(int sock, clientrequest *req)
{
  char* fbuf;
  int bytesread, retval;
  serverresponse resp;

  /* Daten ausgeben */
  printf("Client requests file: %s\n", req->filename);
  fflush(stdout);

  /* Angeforderte Datei lesen */
  bytesread = getFile(req->filename, &fbuf);

  /* Datei nicht gefunden */
  if(bytesread == -1) {
    /* Datei nicht gefunden, error senden */
    resp.retcode = FP_FILENOTFOUND;
    resp.filelen = 0;
    
    retval = send_response_and_file(sock, resp, NULL);
  }

  /* Datei gefunden */
  else {
    /* Datei gefunden, OK und Datei senden */
    resp.retcode = FP_OK;
    resp.filelen = bytesread;

    retval = send_response_and_file(sock, resp, fbuf);
  }
  return retval;
}


int main(int argc, char **argv)
{

  short svport;
  int listensocket;


  /* Argumente auslesen */
  if (extractArgs(argc, argv,&svport)) {
    err("Error while processing arguments\n");
  }

  /* listensocket erzeugen und vorbereiten */
  if(create_listensocket(&listensocket, svport)) {
    err("Error in listensocket()\n");
  }

  printf("Server is listening on port %d\n", svport);
  fflush(stdout);

  /* Service-Schleife */
  while (1) {
    int connsocket, retval;
    clientrequest req;
    
    /* Eingehende Verbindung akzeptieren */
    connsocket = accept_client(listensocket);

    /* Eingabe: Client-Request vom socket lesen */
    retval = recv_clientrequest(connsocket, &req);
    if(retval) {
      fprintf(stderr, "receiving data failed\n");
      close(connsocket);
      continue;
    }
    
    /* Verarbeitung und evtl. R�ckgabe an den Client */
    switch(req.cmd) {
    
      case FP_GET:
        retval = process_get_request(connsocket, &req);
        if(retval) {
           close(connsocket);
           fprintf(stderr, "process_get_request() failed\n");
           continue;
        }
      break;
      
      default:
        printf("Unknown Clientrequest");
    }

    /* Verbindung beenden und socket freigeben */
    close(connsocket);
  }
}
