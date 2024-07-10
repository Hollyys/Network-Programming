// HTTP 요청 생성 예제
// libcurl 라이브러리를 사용

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

        // If you want to set headers
        struct curl_slist *headers = NULL;
        // curl_slist_append 함수를 이용해 HTTP 헤더를 설정합니다.
        headers = curl_slist_append(headers, "Accept: application/json");
        // Accept 헤더는 클라이언트가 받아들일 수 있는 콘텐츠 타입을 나타냅니다.
        headers = curl_slist_append(headers, "Content-Type: application/json");
        // Content-Type 헤더는 클라이언트가 서버에 전송하는 본문의 타입을 나타냅니다.
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // 이 외에도 HTTP 요청에 필요한 다양한 설정을 할 수 있습니다.
        // 예를 들어, CURLOPT_POST 옵션을 사용해 POST 메서드를 사용하도록 설정하고,
        // CURLOPT_POSTFIELDS 옵션을 사용해 본문 데이터를 설정할 수 있습니다. 

        res = curl_easy_perform(curl);
        // 요청을 보내고 나서는 curl_easy_perform 함수로 요청을 실행합니다.
        // 만약 요청에 실패하면, curl_easy_strerror 함수를 사용해 오류 메시지를 출력할 수 있습니다. 
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        // 모든 작업이 끝나면 curl_easy_cleanup 함수를 사용해 초기화된 CURL 핸들을 해제
    }

    curl_global_cleanup();
    // curl_global_cleanup 함수로 libcurl 라이브러리를 정리
    return 0;
}
