#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXBUF 80

void child_func(int childnum, char *servIP, int port);

int main(int argc, char *argv[])
{
    int nchildren = 1;
    char *servIP;
    int port;
    int pid;
    int i;

    if (argc < 4) {
      fprintf(stderr, "Uzycie: %s <serwer> <port> <liczba klientow>\n",
              argv[0]);
      exit(1);
    }
    servIP=argv[1];
    port=atoi(argv[2]);
    nchildren = atoi(argv[3]);
    
    for (i = 0; i < nchildren; i++) {
        if ((pid = fork()) == 0) {
            child_func(i + 1, servIP, port);
            exit(0);
        }
    }
    wait(NULL);
    return 0;
}

void child_func(int childnum, char *servIP, int port)
{
    int sock;
    struct sockaddr_in sAddr;
    char buffer[MAXBUF];
    

    sock = socket(PF_INET, SOCK_STREAM, 0);
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = inet_addr(servIP);
    sAddr.sin_port = htons(port);
    
    if (connect(sock, (const struct sockaddr *) &sAddr, sizeof(sAddr)) != 0) {
      perror("klient");
      return;
    }
      
    snprintf(buffer, MAXBUF, "Dane od klienta %i.", childnum);
    sleep(1);
    printf("Potomek %i wyslal %i znakow\n", childnum, 
            write(sock, buffer, strlen(buffer)));
    sleep(1);
    printf("Potomek %i otrzymal %i znakow\n", childnum, 
            read(sock, buffer, MAXBUF));
    sleep(1);
    close(sock);
}
