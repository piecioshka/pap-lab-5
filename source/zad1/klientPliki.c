#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../library/utils.h"

int main(int argc, char * argv[]) {
    int sock_id;

    char * ip_address;
    int port;
    char * filename;

    struct sockaddr_in xferServer;

    int counter;
    int fd;
    int returnStatus;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <ip address> <port> <filename> [dest filename]\n", argv[0]);
        exit(1);
    }

    ip_address = argv[1];
    /* get port from param and convert this string to integer */
    port = atoi(argv[2]);
    filename = argv[3];

    /* wpisz informacje o serwerze */
    memset(&xferServer, 0, sizeof(xferServer));
    xferServer.sin_family = AF_INET;
    xferServer.sin_addr.s_addr = inet_addr(ip_address);
    xferServer.sin_port = htons(port);
    
    printf("=== create client instance ===\n\n");

    /* create socket to connection */
    sock_id = create_socket_tcp();

    /* use create socket to connect address */
    create_connection(sock_id, xferServer);

    /* wyslij nazwe pliku */
    send_string(xferServer, & filename);

    if (returnStatus == -1) {
        fprintf(stderr, "Could not send filename to server!\n");
        exit(1);
    }

    /* zamknij polaczenie jednostronnie */
    shutdown(sock_id);

    /* otworz plik do zapisu */
    fd = open(filename, O_RDWR);

    if (fd == -1) {
        fprintf(stderr, "Could not open destination file, using stdout.\n");
        fd = 1;
    }
 
    /* czytaj plik z serwera */
    receive_from_server(sock_id);

    if (counter == -1) {
        fprintf(stderr, "Could not read file from socket!\n");
        exit(1);
    }

    close(sock_id);
    return 0;
}
