// TCP(Transmission Control Protocol)와 UDP(User Datagram Protocol)는 이러한 IP 위에서 동작하는 프로토콜로, 데이터의 전송 방식을 담당합니다.
// TCP는 연결 지향적이고 신뢰할 수 있는 데이터 전송을 보장하지만, UDP는 연결 없이 데이터를 전송하기 때문에 빠른 전송을 가능하게 하지만 신뢰성은 낮습니다.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <string.h> // for strlen
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_addr  

int main() {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];  

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");  

    server.sin_addr.s_addr = inet_addr("192.0.2.33");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }  

    puts("Connected\n");  

    // keep communicating with server
    while(1) {
        printf("Enter message : ");
        scanf("%s", message);  

        // Send some data
        if(send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }
        // Receive a reply from the server
        if(recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }  

        puts("Server reply :");
        puts(server_reply);
    }  

    close(sock);
    return 0;
}

// 위의 코드는 C로 작성된 TCP 기반의 클라이언트 예제입니다.
// 소켓을 생성하고, 서버에 연결하고, 메시지를 보내고, 응답을 받는 과정을 보여줍니다.
// UDP를 사용하는 경우에는 SOCK_STREAM을 SOCK_DGRAM으로 변경하고, connect, send, recv 대신에 sendto, recvfrom을 사용하게 됩니다.