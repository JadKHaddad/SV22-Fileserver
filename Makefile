CC=gcc
CFLAGS=-ggdb -Wall -Werror -pedantic-errors

all: fileclient fileserver

fileclient: fileclient.o clientnetoperations.o common.o
fileserver: fileserver.o fileoperations.o servernetoperations.o common.o

fileclient.o: fileclient.c common.h fileoperations.h
fileserver.o: fileserver.c common.h fileoperations.h
fileoperations.o: fileoperations.c  fileoperations.h
servernetoperations.o: servernetoperations.c servernetoperations.h common.h fileprotocol.h
clientnetoperations.o: clientnetoperations.c clientnetoperations.h common.h fileprotocol.h
common.o: common.c common.h

clean: 
	-rm *.o fileclient fileserver *~

dist: 
	-rm *.o
