// TCP 소켓을 이용하여 '127.0.0.1'이라는 IP 주소와 1234 포트에 "Hello, World!"라는 메시지를 전송

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }  

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(1234); // Port 1234
    if (inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr) <= 0) {
        perror("Failed to setup socket address");
        exit(EXIT_FAILURE);
    }  

    if (connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }  

    const char *message = "Hello, World!";
    if (write(sockfd, message, strlen(message)) < 0) {
        perror("Failed to send message");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    return 0;
}
