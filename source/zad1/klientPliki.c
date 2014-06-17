#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAXBUF 1024

int main(int argc, char * argv[]) {
    int sockd;
    int counter;
    int fd;
    struct sockaddr_in xferServer;
    char buf[MAXBUF];
    int returnStatus;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <ip address> <port> <filename> [dest filename]\n", argv[0]);
        exit(1);
    }

    /* utworz gniazdo */
    sockd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockd == -1) {
        fprintf(stderr, "Could not create socket!\n");
        exit(1);
    }

    /* wpisz informacje o serwerze */
    xferServer.sin_family = AF_INET;
    xferServer.sin_addr.s_addr =
    xferServer.sin_port =

    /* polacz z serwerem */
    returnStatus = connect(sockd, (struct sockaddr*)&xferServer, sizeof(xferServer));

    if (returnStatus == -1) {
        fprintf(stderr, "Could not connect to server!\n");
        exit(1);
    }

    /* wyslij nazwe pliku */
    ....

    if (returnStatus == -1) {
        fprintf(stderr, "Could not send filename to server!\n");
        exit(1);
    }

    /* zamknij polaczenie jednostronnie */
    ....

    /* otworz plik do zapisu */
    ....

    if (fd == -1) {
        fprintf(stderr, "Could not open destination file, using stdout.\n");
        fd = 1;
    }

    /* czytaj plik z serwera */
    ....

    if (counter == -1) {
        fprintf(stderr, "Could not read file from socket!\n");
        exit(1);
    }

    close(sockd);
    return 0;
}
