#include <stdio.h>
#include <stdlib.h>      // for exit
#include <string.h>      // for memset, memcpy, strlen
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>// for close

#define SERVER_PORT 5432
#define MAX_LINE 256

int main(int argc, char *argv[])
{
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    if (argc == 2)
    {
        host = argv[1];
    }
    else
    {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* translate host name into peer's IP address */
    hp = gethostbyname(host);
    if (!hp)
    {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    /* build address data structure */
    memset(&sin, 0, sizeof(sin));   // Correct replacement for bzero
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr, hp->h_addr_list[0], hp->h_length);  // Correct replacement for bcopy
    sin.sin_port = htons(SERVER_PORT);

    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }

    /* main loop: get and send lines of text */
    while (fgets(buf, sizeof(buf), stdin))
    {
        len = strlen(buf);
        if (send(s, buf, len, 0) < 0)  // Check for errors in send
        {
            perror("simplex-talk: send");
            exit(1);
        }
    }

    close(s);  // Always close the socket at the end
}
