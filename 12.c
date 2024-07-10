// HTTP 응답 처리 예제

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + totalSize + 1);
    if(ptr == NULL) {
        // 메모리를 확장할 수 없습니다
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, totalSize);
    mem->size += totalSize;
    mem->memory[mem->size] = 0;

    return totalSize;
}

int main() {
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // 메모리를 1바이트 할당
    chunk.size = 0;            // 크기를 0으로 초기화

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        // CURLOPT_WRITEFUNCTION과 CURLOPT_WRITEDATA 옵션을 사용해
        // 서버로부터 받은 데이터를 어떻게 처리할지를 설정
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // CURLOPT_WRITEFUNCTION에는 콜백 함수를 지정합니다.
        // 이 함수는 서버로부터 데이터를 받을 때 호출되며,
        // 데이터의 포인터와 크기, 데이터 블록의 수 등을 인자로 받습니다.
        // 이 함수는 받은 데이터를 처리하고, 처리한 데이터의 크기를 반환해야 합니다.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        // CURLOPT_WRITEDATA에는 콜백 함수의 마지막 인자로 전달될 데이터를 지정합니다.
        // 이 예제에서는 MemoryStruct 객체의 주소를 지정했으며,
        // 이 객체에 서버로부터 받은 데이터를 저장합니다.

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", chunk.memory);
        }

        // 클린업
        curl_easy_cleanup(curl);
        free(chunk.memory);
    }

    curl_global_cleanup();
    return 0;
}
