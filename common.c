#include "common.h"

void err(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/* Sendet *len Bytes beginnend bei msg ueber sock,
   Gibt -1 bei Fehler und 0 bei Erfolg zurück,
   Tatsächliche Anzahl gesendeter Bytes wird in len geschrieben.
   Implementieren Sie partielles senden (siehe Übung 2). */
int sendMsg(int sock, char *msg, int *len)
{
    int total = 0;        /* bisher gesendet */
    int bytesleft = *len; /* Restmenge zu Senden */
    int currsent = 0;     /* In diesem Lauf gesendet */
    while (total < *len)
    {
        currsent = send(sock, msg + total, bytesleft, 0);
        if (currsent == -1)
        {
            perror("send");
            return -1;
        }
        total += currsent;
        bytesleft -= currsent;
    }

    return 0;
}