// 위의 C 코드는 IP 주소를 문자열로부터 바이너리 형태로 변환하고 다시 문자열로 변환하는 과정을 보여줍니다.
// inet_pton과 inet_ntop 함수는 각각 프레젠테이션 형태의 주소를 네트워크 바이트 순서의 바이너리 형태로, 그 반대로 변환하는 데 사용됩니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset
#include <arpa/inet.h> // for inet_addr  

int main() {
    struct sockaddr_in sa;
    char str[INET_ADDRSTRLEN];  

    // store this IP address in sa:
    inet_pton(AF_INET, "192.0.2.33", &(sa.sin_addr));  

    // now get it back and print it
    inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);  

    printf("%s\n", str); // prints "192.0.2.33"  

    return 0;
}