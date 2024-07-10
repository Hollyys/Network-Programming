// 아래 코드는 서버가 클라이언트로부터 데이터를 받는 간단한 예제입니다.
// 우선, 서버는 소켓을 생성하고, IP 주소와 포트 번호를 설정하여 소켓을 바인드 합니다.
// 그다음, 클라이언트로부터의 연결 요청을 기다리며, 연결 요청이 들어오면 이를 수락하고 데이터를 읽어 들입니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buffer[256];

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);

    // 소켓 바인딩
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        close(sockfd);
        exit(1);
    }

    // 연결 대기
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // 클라이언트 연결 수락
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        close(sockfd);
        exit(1);
    }

    bzero(buffer, 256);
    // 데이터 읽기
    if (read(newsockfd, buffer, 255) < 0) {
        perror("ERROR reading from socket");
        close(newsockfd);
        close(sockfd);
        exit(1);
    }

    printf("Here is the message: %s\n", buffer);

    close(newsockfd);
    close(sockfd);
    return 0;
}
