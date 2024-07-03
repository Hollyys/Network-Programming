// 이 코드는 클라이언트 소켓을 생성하고, 서버에 연결하여 메시지를 전송하는 기본적인 과정을 보여줍니다.

// socket(), connect(), send() 등의 함수를 이용해 네트워크 통신을 구현하고 있습니다.
// socket() 함수는 소켓을 생성
// connect() 함수는 해당 소켓을 특정 IP 주소와 포트 번호를 가진 서버에 연결하는 데 사용
// send() 함수는 연결된 서버에 메시지를 전송하는 데 사용

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  

int main() {
    // 소켓 생성
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // socket 함수는 세 개의 인자를 받습니다.
    // 첫 번째 인자 AF_INET은 주소 체계(address family)를 의미하며, IPv4 인터넷 프로토콜을 사용하겠다는 것을 나타냅니다.
    // 두 번째 인자 SOCK_STREAM은 소켓 타입을 나타내며, 이 경우 TCP 소켓을 사용하겠다는 것을 의미합니다.
    // 세 번째 인자는 특정 프로토콜을 지정하는 데 사용되지만, 일반적으로 0을 사용하여 기본 프로토콜을 사용하도록 합니다.
    
    // 서버 주소 구조체 설정
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);  // 서버 포트 번호
    inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));  // 서버 IP 주소  

    // 서버에 연결
    connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));  

    // 서버에 메시지 전송
    std::string message = "Hello, Server!";
    send(sockfd, message.c_str(), message.size(), 0);  

    // 소켓 닫기
    close(sockfd);  

    return 0;
}