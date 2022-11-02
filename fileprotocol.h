/* fileprotocol.h */
#ifndef FILEPROTOCOL_H_INCLUDED
#define FILEPROTOCOL_H_INCLUDED

#define FP_MAXFILENAME 64

enum file_clientcommand
{
    FP_GET
};

enum file_serverretcode
{
    FP_OK = 0,
    FP_BADREQUEST,
    FP_FILENOTFOUND,
    FP_GENERROR
};


typedef struct
{
    int reqlen;
    int cmd;
    char filename[FP_MAXFILENAME];
} clientrequest;


typedef struct
{
    int retcode;
    int filelen;
} serverresponse;

#endif
