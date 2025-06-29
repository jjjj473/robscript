#include "web_block.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void block_start_server(void) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8080);

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(s);
        return;
    }

    if (listen(s, 1) < 0) {
        perror("listen");
        close(s);
        return;
    }

    printf("Serving http://localhost:8080 ... (single request)\n");
    int c = accept(s, NULL, NULL);
    if (c >= 0) {
        const char resp[] =
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>Hello from robbuilder!</h1></body></html>";
        send(c, resp, sizeof(resp) - 1, 0);
        close(c);
    }
    close(s);
}
