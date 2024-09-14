#include <stdio.h>
#include <stdlib.h>      // for exit
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>      // for memset

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256

int main()
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    socklen_t len;
    int s, new_s;
    /* build address data structure */
    memset(&sin, 0, sizeof(sin));  // Correct replacement for bzero
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("simplex-talk: bind");
        exit(1);
    }
    if (listen(s, MAX_PENDING) < 0)
    {
        perror("simplex-talk: listen");
        exit(1);
    }

    /* wait for connection, then receive and print text */
    while (1)
    {
        len = sizeof(sin);
        if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0)
        {
            perror("simplex-talk: accept");
            exit(1);
        }
        ssize_t n;
        while ((n = recv(new_s, buf, sizeof(buf), 0)) > 0)
        {
            fputs(buf, stdout);
        }
        if (n < 0)
        {
            perror("simplex-talk: recv");
        }
        close(new_s);
    }
}
