#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(5000),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    bind(server, (struct sockaddr *)&addr, sizeof(addr));
    listen(server, 5);

    int client = accept(server, NULL, NULL);

    char buf[1024];
    ssize_t n = recv(client, buf, sizeof(buf), 0);
    if (n > 0)
        send(client, buf, n, 0);

    close(client);
    close(server);
}
