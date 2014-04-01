#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

#include "../lib/libnetutils.h"

#define MAXBUF 1024
#define MAX_QUEUE 128

int main (int argc, char * argv[]) {
    int sock_id1, sock_id2, port;
    socklen_t addrlen;
    struct sockaddr_in xferServer, xferClient;

    /* check params */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server port>\n", argv[0]);
        exit(1);
    }

    /* get port from param and convert this string to integer */
    port = atoi(argv[1]);

    /* przypisz adres gniazdu */
    memset(&xferServer, 0, sizeof(xferServer));
    xferServer.sin_family = AF_INET;
    xferServer.sin_addr.s_addr = INADDR_ANY;
    xferServer.sin_port = htons(port);

    printf("=== create server instance ===\n\n");

    /* create socket to connection */
    sock_id1 = create_socket_tcp();

    /* bind server to defined port */
    bind_port(sock_id1, xferServer);

    /* server waiting for client */
    listen_for_client_tcp(sock_id1, MAX_QUEUE);

    for (;;) {
        int fd;
        int i, readCounter, writeCounter;
        char* bufptr;
        char buf[MAXBUF];
        char filename[MAXBUF];

        /* czekaj na klienta */
        addrlen = sizeof (xferClient);

        sock_id2 = accept(sock_id1, (struct sockaddr *) & xferClient, & addrlen);

        if (sock_id2 == -1) {
            fprintf(stderr, "ERROR: Could not accept connection!\n");
            exit(1);
        }

        /* pobierz nazwe pliku */
        i = 0;

        if ((readCounter = read(sock_id2, filename + i, MAXBUF)) > 0) {
            i += readCounter;
        }

        if (readCounter == -1) {
            fprintf(stderr, "ERROR: Could not read filename from socket!\n");
            close(sock_id2);
            continue;
        }

        filename[i + 1] = '\0';

        printf("Reading file %s\n", filename);

        /* otworz plik do czytania */
        fd = open(filename, O_RDONLY);

        if (fd == -1) {
            fprintf(stderr, "ERROR: Could not open file for reading!\n");
            close(sock_id2);
            continue;
        }

        readCounter = 0;

        /* czytaj plik i przesylaj do klienta */
        while ((readCounter = read(fd, buf, MAXBUF)) > 0) {
            writeCounter = 0;
            bufptr = buf;

            while (writeCounter < readCounter) {
                readCounter -= writeCounter;
                bufptr += writeCounter;
                writeCounter = write(sock_id2, bufptr, readCounter);

                if (writeCounter == -1) {
                    fprintf(stderr, "ERROR: Could not write file to client!\n");
                    close(sock_id2);
                    continue;
                }
            }
        }

        close(sock_id2);
        close(fd);

    }

    close(sock_id1);
    return 0;
}
