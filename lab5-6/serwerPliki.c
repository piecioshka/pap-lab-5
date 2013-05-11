#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

#define MAXBUF		1024

int main(int argc, char *argv[])
{

    int socket1,socket2;
    int addrlen;
    struct sockaddr_in xferServer, xferClient;
    int returnStatus;

    /* utworz gniazdo */
    socket1 = socket(AF_INET, SOCK_STREAM, 0);
  
    if (socket1 == -1)
    {
        fprintf(stderr, "Could not create socket!\n");
        exit(1);
    }

    /* przypisz adres gniazdu */
    xferServer.sin_family = AF_INET;
    xferServer.sin_addr.s_addr = INADDR_ANY;
    xferServer.sin_port = ....

    returnStatus = bind(socket1, (struct sockaddr*)&xferServer, sizeof(xferServer));
  
    if (returnStatus == -1)
    {
        fprintf(stderr, "Could not bind to socket!\n");
        exit(1);
    }

    returnStatus = listen(socket1, 5);

    if (returnStatus == -1)
    {
        fprintf(stderr, "Could not listen on socket!\n");
        exit(1);
    }

    for(;;)
    {

        int fd;
        int i, readCounter, writeCounter;
        char* bufptr;
        char buf[MAXBUF];
        char filename[MAXBUF];
  
        /* czekaj na klienta */
        addrlen = sizeof(xferClient);

        socket2 = accept(socket1, (struct sockaddr*)&xferClient, &addrlen);
    
        if (socket2 == -1)
        {
            fprintf(stderr, "Could not accept connection!\n");
            exit(1);
        }
 
        /* pobierz nazwe pliku */
        i = 0;

        if ((readCounter = read(socket2, filename + i, MAXBUF)) > 0)
        {
            i += readCounter;
        }
    
        if (readCounter == -1)
        {
            fprintf(stderr, "Could not read filename from socket!\n");
            close(socket2);
            continue;
        }

        filename[i+1] = '\0';

        printf("Reading file %s\n", filename);
 
        /* otworz plik do czytania */
        fd = 

        if (fd == -1)
        {
            fprintf(stderr, "Could not open file for reading!\n");
            close(socket2);
            continue;
        }

        readCounter = 0;

        /* czytaj plik i przesylaj do klienta */
        while((readCounter = read(fd, buf, MAXBUF)) > 0)
        {
            writeCounter = 0;
            bufptr = buf;

            while (writeCounter < readCounter)
            {
        
                readCounter -= writeCounter;
                bufptr += writeCounter;
                writeCounter = write(socket2, bufptr, readCounter);
        
                if (writeCounter == -1) 
                {
                    fprintf(stderr, "Could not write file to client!\n");
                    close(socket2); 
                    continue;
                }
            }
        }

        close(socket2); 
        close(fd);

    }

  close (socket1);
  return 0;

}
