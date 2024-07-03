// UDP 기반의 클라이언트 예제입니다. 소켓을 생성하고, 서버에 메시지를 보내고, 응답을 받는 과정을 보여줍니다.
// TCP와 달리 UDP는 연결을 맺지 않고 데이터를 전송하므로, 데이터를 보낼 때마다 대상의 주소를 지정해야 합니다.
// 따라서 sendto, recvfrom 함수를 사용하여 메시지를 전송하고 응답을 받게 됩니다.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <string.h> // for strlen
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_addr  

int main() {
    int sock;
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    char message[1000], buf[1024];  

    // Create a UDP socket
    if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }  

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(8888);  

    if (inet_aton("192.0.2.33", &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }  

    // keep communicating with server
    while(1) {
        printf("Enter message : ");
        scanf("%s", message);  

        // Send message
        if (sendto(sock, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1) {
            perror("sendto()");
            exit(1);
        }  

        // Receive a reply
        memset(buf, '\0', sizeof(buf));
        if (recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen) == -1) {
            perror("recvfrom()");
            exit(1);
        }  

        puts("Server reply :");
        puts(buf);
    }  

    close(sock);
    return 0;
}