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

int main(int argc, char *argv[]) {
    char * servIP;
    int nchildren, port, pid, i;

    // Sprawdzamy czy liczba argumentów nie jest mniejsza niż 4?
    if (argc < 4) {
        // Jest mniejsza, drukujemy na standardowym strumieniu do błędów informację.
        fprintf(stderr, "Uzycie: %s <serwer> <port> <liczba klientow>\n", argv[0]);
        // Przerywamy działanie problemu.
        exit(1);
    }

    // Nazwa serwera.
    servIP = argv[1];
    // Port.
    port = atoi(argv[2]);
    // Liczba klientów obsługiwanych.
    nchildren = atoi(argv[3]);

    for (i = 0; i < nchildren; i++) {
        // Tworzymy proces, poprzez rozgałęzienie bieżącego.
        if ((pid = fork()) == 0) {
            // Jeśli tworzenie się udało to... ?!??!?
            child_func(i + 1, servIP, port);
            exit(0);
        }
    }

    wait(NULL);
    return 0;
}

void child_func(int childnum, char *servIP, int port) {
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
    printf("Potomek %i wyslal %i znakow\n", childnum, (int) write(sock, buffer, strlen(buffer)));

    sleep(1);
    printf("Potomek %i otrzymal %i znakow\n", childnum, (int) read(sock, buffer, MAXBUF));

    sleep(1);
    close(sock);
}
