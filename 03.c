// C언어를 이용하여 HTTP 요청을 보내는 예제입니다.
// 이렇게 C/C++는 운영 체제 레벨에서 제공하는 네트워크 API를 직접적으로 호출하며, 이를 통해 사용자가 네트워크에 대한 깊은 이해를 갖게 합니다.

#include <stdio.h>
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>   

int main() {
    int socket_desc;
    struct sockaddr_in server;
    char *message;  

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }  

    server.sin_addr.s_addr = inet_addr("93.184.216.34"); // example.com
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );  

    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
        puts("connect error");
        return 1;
    }  

    puts("Connected\n");  

    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0) {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");  

    close(socket_desc);  

    return 0;
}