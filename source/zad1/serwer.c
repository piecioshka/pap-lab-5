#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXBUF 80

int main(int argc, char *argv[])
{
    struct sockaddr_in sAddr;
    int listensock;
    int sock_cli;
    int servPort;
    char buffer[25];
    int result;
    int nread;

    if (argc != 2) {
       fprintf(stderr, "Uzycie: %s <Port>\n",argv[0]);
       exit(1);
    }

    listensock = socket(PF_INET, SOCK_STREAM, 0);
    if (listensock <0) {
       perror("serwer");
       exit(1);
    }
    servPort=atoi(argv[1]);

    sAddr.sin_family = AF_INET;
    sAddr.sin_port = htons(servPort);
    sAddr.sin_addr.s_addr = INADDR_ANY;
    result = bind(listensock, (struct sockaddr *) &sAddr, sizeof(sAddr));
    if (result < 0) {
        perror("serwer");
        exit(1);
    }
    result = listen(listensock, 5);
    if (result < 0) {
        perror("serwer");
        exit(1);
    }

    while (1) {
        sock_cli = accept(listensock, NULL ,NULL);
        if (sock_cli < 0) {
          perror("serwer");
          exit(1);
        }
        nread = read(sock_cli, buffer, MAXBUF-1);
        buffer[nread] = '\0';
        fprintf(stdout,"%s\n", buffer);
        write(sock_cli, buffer, nread);
        close(sock_cli);
   }
}
