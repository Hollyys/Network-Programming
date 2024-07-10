// 아래 클라이언트 코드는 서버로 데이터를 보내는 간단한 예제입니다.
// 클라이언트는 먼저 소켓을 생성하고, 연결할 서버의 IP 주소와 포트 번호를 설정합니다.
// 그 다음, 서버에 연결 요청을 보내고, 사용자로부터 입력받은 데이터를 서버로 전송합니다. 

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>  

int main() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];  

    portno = 5000;
    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname("localhost");  

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);  

    // 서버에 연결
    connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);  

    // 데이터 쓰기
    write(sockfd,buffer,strlen(buffer));  

    close(sockfd);
    return 0;
}