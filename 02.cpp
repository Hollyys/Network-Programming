// TCP 소켓을 이용하여 '127.0.0.1'이라는 IP 주소와 1234 포트에 "Hello, World!"라는 메시지를 전송

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>  

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }  

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(1234); // Port 1234
    if (inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr) <= 0) {
        std::cerr << "Failed to setup socket address. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }  

    if (connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cerr << "Failed to connect. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }  

    write(sockfd, "Hello, World!", 13);
    close(sockfd);
    return 0;
}