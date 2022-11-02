/* fileoperations.c */

#include "fileoperations.h"

int getFile(const char* path, char** buf)
{
  int retval = 0;
  int fd = -1;
  struct stat sb;
  char *fptr;

  /* ueberpruefen ob Datei vorhanden und regulaer */
  retval = stat(path, &sb);
  if (retval == -1) {
    fprintf(stderr, "%s: ", path);
    perror("");
    return -1;
  }
  if (!S_ISREG(sb.st_mode)){
    fprintf(stderr, "%s is not a regular file!\n", path);
    return -1;
  }
  
  /* oeffnen */
  fd = open(path, O_RDONLY);
  if (fd == -1 ) {
    fprintf(stderr, "%s - ", path);
    perror("open");
    exit(EXIT_FAILURE);
  }
  /* in den Speicher abbilden */
  fptr = (char *) mmap (NULL, sb.st_size, PROT_READ, 
      MAP_SHARED, fd, 0);
  if (fptr ==  MAP_FAILED) 
  {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  
  /* lesen erfolgreich set ptr und return size */
  *buf = fptr;
  return sb.st_size;
}
