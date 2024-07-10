# Network-Programming  
## 참조 URL:  
https://gdngy.tistory.com/186  
  
# 네트워크 보안 개념  

네트워크 보안은 정보와 정보를 전송하는 네트워크 자체를 보호하는 과정을 의미합니다. 주요 보안 목표는 기밀성, 무결성, 가용성(CIA)이며, 이를 위해 인증, 인가, 부인방지 등의 메커니즘이 사용됩니다. 인터넷에서 가장 많이 사용하는 보안 프로토콜은 TLS와 SSL입니다. 이 프로토콜들은 데이터를 암호화하고, 상대방의 신원을 확인하며, 데이터 무결성을 보장합니다. C/C++ 프로그래머는 이런 보안 메커니즘을 이해하고, 적용해야 합니다.  
  
## 14.5.1. 암호화 및 디지털 서명
암호화란 정보를 변조하여 원래의 내용을 알 수 없도록 하는 과정을 의미합니다. 이를 통해 기밀성을 보장하며, 무단 사용자가 정보를 열람하는 것을 방지합니다. 디지털 서명은 암호화와 반대 개념으로, 원본 데이터가 변조되지 않았음을 증명하는 역할을 합니다.

### 암호화
두 가지 주요 암호화 유형이 있습니다: 대칭 키 암호화와 비대칭 키 암호화.  

대칭키 암호화에서는 암호화와 복호화에 같은 키가 사용됩니다. 가장 일반적인 대칭키 암호화 알고리즘은 AES(Advanced Encryption Standard)입니다. C++로 AES를 구현한 간단한 예제는 다음과 같습니다.  

[예제]

// 주: 이 코드는 예시용으로, 실제 보안 상황에서는 적합하지 않을 수 있습니다.
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>  

void aes_encrypt(std::string plaintext, byte* key, std::string& ciphertext) {
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);  

    CryptoPP::StringSource(plaintext, true, 
        new CryptoPP::StreamTransformationFilter(ecbEncryption, new CryptoPP::StringSink(ciphertext)));
}

비대칭키 암호화는 암호화와 복호화에 서로 다른 키를 사용합니다. 가장 널리 사용되는 비대칭키 암호화 알고리즘은 RSA입니다.

### 디지털 서명
디지털 서명은 전자 문서에 붙여, 해당 문서가 변조되지 않았음을 증명하는 역할을 합니다. C++로 RSA 디지털 서명을 구현한 간단한 예제는 다음과 같습니다.  

[예제]

// 주: 이 코드는 예시용으로, 실제 보안 상황에서는 적합하지 않을 수 있습니다.
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>  

void rsa_sign(std::string message, CryptoPP::RSA::PrivateKey privateKey, std::string& signature) {
    CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);  

    CryptoPP::StringSource(message, true, 
        new CryptoPP::SignerFilter(CryptoPP::AutoSeededRandomPool(), signer,
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(signature))));
}
 

암호화와 디지털 서명을 이해하고 구현하는 것은 네트워크 보안의 핵심적인 요소입니다. 그러나, 이들은 매우 복잡하고, 잘못 구현하면 심각한 보안 위험을 초래할 수 있으므로, 가능한 한 표준 라이브러리를 사용하는 것이 좋습니다. 또한, 이러한 알고리즘을 사용할 때는 해당 국가의 암호화에 관한 법률을 반드시 준수해야 합니다. 

 

### 14.5.2. SSL/TLS를 이용한 네트워크 통신  

SSL(Secure Sockets Layer) 및 TLS(Transport Layer Security)는 인터넷상에서 데이터를 안전하게 전송하기 위해 널리 사용되는 프로토콜입니다. 둘 다 데이터 암호화, 서버 및 클라이언트 인증, 메시지 무결성을 제공하여 네트워크 통신의 안전성을 보장합니다. 

### SSL과 TLS의 기본적인 동작 방식
클라이언트와 서버 사이의 SSL/TLS 연결 설정은 '안전한 핸드셰이크'를 통해 이루어집니다. 이 과정에서 클라이언트와 서버는 서로를 인증하고, 암호화 방법을 협상하며, 암호화된 연결을 위한 '세션 키'를 생성합니다.  

### SSL/TLS의 사용
대부분의 최신 HTTP 라이브러리는 SSL/TLS를 내장하고 있습니다. 따라서 C++ 프로그래머가 직접 SSL/TLS를 구현할 필요는 거의 없습니다. 그러나 어떻게 작동하는지 이해하는 것이 중요합니다.  

C++로 작성된 간단한 HTTPS 클라이언트 예제는 아래와 같습니다. 이 예제에서는 libcurl 라이브러리를 사용합니다.  

[예제]

// 주: 이 코드는 예시용으로, 실제 보안 상황에서는 적합하지 않을 수 있습니다.
#include <curl/curl.h>  

int main() {
    CURL *curl;
    CURLcode res;  

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();  

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");
        res = curl_easy_perform(curl);  

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }  

        curl_easy_cleanup(curl);
    }  

    curl_global_cleanup();  

    return 0;
}

이 코드는 "https://www.example.com"으로 HTTPS 요청을 보내는 역할을 합니다. libcurl 라이브러리는 내부적으로 SSL/TLS를 처리하여 데이터를 안전하게 전송합니다.  

SSL/TLS는 웹에서 가장 널리 사용되는 보안 프로토콜 중 하나입니다. 따라서, 웹 기반의 애플리케이션을 개발하거나, 웹 API에 연결하는 C++ 프로그램을 작성할 때에는 항상 SSL/TLS를 사용하여 통신해야 합니다. 

가장 중요한 보안 고려사항 중 하나는 암호화입니다. 데이터를 암호화하면, 데이터가 전송 경로에서 도난당하더라도 해독하는 데 키가 필요하므로 데이터를 안전하게 유지할 수 있습니다. SSL/TLS는 이러한 암호화를 제공하는 중요한 도구입니다.

하지만 SSL/TLS는 완벽한 보안을 보장하지는 않습니다. 공격자가 네트워크 트래픽을 감시하고 있으면, '중간자 공격(Man-in-the-middle attack)'을 시도하여 통신을 해독하려고 할 수 있습니다. 이를 방지하기 위해 SSL/TLS는 '서버 인증'을 포함합니다. 이는 클라이언트가 서버와 통신하려 할 때 서버의 신원을 검증하는 과정입니다.

서버 인증은 '디지털 인증서'를 사용하여 수행됩니다. 이 인증서는 신뢰할 수 있는 제3자인 '인증 기관(CA)'에 의해 발급되며, 클라이언트가 서버와의 연결이 안전하다는 것을 확신하게 해 줍니다.

이런 보안 기법을 이해하고 구현하는 것은 복잡할 수 있지만, 많은 라이브러리와 도구들이 이러한 과정을 단순화하고 자동화하는데 도움을 줍니다. C++에서는 OpenSSL, GnuTLS, libcurl 등의 라이브러리가 이런 목적으로 널리 사용됩니다. 

마지막으로, 보안은 항상 지속적인 고려사항이어야 합니다. 공격자의 기술은 계속 발전하므로, 우리의 보안 방법도 업데이트되고 개선되어야 합니다. 최신 보안 기준을 준수하고, 사용하는 라이브러리와 도구가 최신 상태인지 항상 확인하는 것이 중요합니다. 

SSL/TLS에 대한 개념을 살펴보았습니다. 이제는 실제 코드를 통해 어떻게 이를 구현할 수 있는지 알아보겠습니다. C++를 이용한 SSL/TLS 클라이언트를 만드는데 많이 쓰이는 라이브러리 중 하나는 OpenSSL입니다. 아래는 OpenSSL을 사용한 간단한 예제 코드입니다.

[예제]

#include <iostream>
#include <openssl/ssl.h>
#include <openssl/bio.h>  

int main() {
    // SSL 라이브러리 초기화
    SSL_load_error_strings();
    SSL_library_init();  

    // SSL 컨텍스트 생성
    SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());  

    // BIO 구조체 생성
    BIO * bio = BIO_new_ssl_connect(ctx);  

    // SSL 구조체 생성
    SSL * ssl;
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);  

    // 웹 서버와 연결
    BIO_set_conn_hostname(bio, "www.example.com:https");  

    // 연결 시도
    if(BIO_do_connect(bio) <= 0) {
        std::cerr << "Connection Error" << std::endl;
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return -1;
    }  

    // 서버에 메시지 전송
    BIO_write(bio, "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n", 47);  

    // 응답 받기
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    BIO_read(bio, buf, 1024);  

    std::cout << "Response:\n" << buf << std::endl;  

    // 연결 종료
    BIO_free_all(bio);
    SSL_CTX_free(ctx);  

    return 0;
}

이 코드는 www.example.com에 SSL/TLS 연결을 생성하고, 간단한 HTTP GET 요청을 전송한 다음 응답을 출력합니다. 여기서는 SSL/TLS 연결을 위해 OpenSSL의 BIO 인터페이스를 사용했습니다. BIO 인터페이스는 OpenSSL에서 제공하는 입출력 추상화 계층으로, 소켓이나 파일 등 다양한 IO에 사용될 수 있습니다. 

이 예제를 컴파일하고 실행하려면, OpenSSL 라이브러리를 시스템에 설치해야 하며, 컴파일 명령에 -lssl -lcrypto 옵션을 포함시켜야 합니다. 이 옵션은 컴파일러에게 OpenSSL 라이브러리를 링크하도록 지시합니다. 

g++ your_file.cpp -lssl -lcrypto -o your_program

이 코드와 컴파일 방법은 기본적인 것이므로, 실제 보안이 중요한 애플리케이션에서는 인증서 검증, 에러 처리, 메모리 관리 등 더욱 세밀한 처리가 필요합니다. 

### 14.5.3. 보안이 필요한 이유  
네트워크 프로그래밍에서 보안은 피할 수 없는 중요한 이슈입니다. 그렇다면 왜 보안이 중요한지, 어떤 위협들이 있으며 어떻게 이를 막을 수 있는지에 대해 알아보겠습니다. 

### 데이터의 무결성  
네트워크를 통해 전송되는 데이터는 중간에서 조작될 위험이 있습니다. 이는 통신 내용의 왜곡이나 데이터 손실을 일으킬 수 있습니다. 이런 위협을 방지하기 위해, 데이터의 무결성을 확인하는 알고리즘(예: 해시 함수)을 사용하여 데이터가 변경되었는지 확인할 수 있습니다. 

### 기밀성  
민감한 정보가 네트워크를 통해 전송되는 경우, 중간에서 정보를 가로챌 수 있는 위험이 있습니다. 이를 방지하기 위해 암호화 기술이 사용됩니다. SSL/TLS 같은 프로토콜은 데이터를 안전하게 전송하기 위해 암호화를 사용합니다. 

### 인증  
네트워크에서는 상대방이 주장하는 사람이나 시스템인지를 확인하는 인증 과정이 필요합니다. 이는 디지털 서명, 인증서 등을 이용하여 이루어집니다. 

이런 보안 이슈들을 해결하기 위해 다양한 알고리즘과 기술이 개발되었습니다. 그중 일부를 C++에서 사용하는 방법에 대해 알아봤습니다. 그러나 네트워크 보안은 매우 넓은 분야로, 알아야 할 것이 많습니다. 

아래는 이러한 보안 요소들을 고려하여 작성한 간단한 C++ 코드 예제입니다. 이 코드는 무결성 확인을 위해 해시 함수를 사용하고 있습니다. 

[예제]

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>  

std::string generate_hash(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);  

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }  

    return ss.str();
}  

int main() {
    std::string input = "hello, world!";
    std::string hash = generate_hash(input);
    std::cout << "Hash of '" << input << "': " << hash << std::endl;  

    return 0;
}
 
이 코드는 OpenSSL 라이브러리의 SHA-256 해시 함수를 사용하여 입력 문자열의 해시 값을 계산합니다. 무결성 확인에 사용되는 해시 값은 데이터가 조금만 변경되어도 완전히 다른 값이 나오므로, 중간에서 데이터가 변경되었는지 쉽게 확인할 수 있습니다.

보안을 고려한 네트워크 프로그래밍은 어렵지만 매우 중요합니다. 이해하고 적용하는 데에는 시간과 노력이 필요하겠지만, 이 과정을 통해 보다 안전한 프로그램을 작성하는 법을 배울 수 있습니다.

코드의 세부 내용을 보면 generate_hash 함수는 OpenSSL의 SHA-256 알고리즘을 사용하여 해시를 생성합니다. 해시는 원본 데이터에서 작은 변화라도 다른 해시 값을 생성하는 특징을 가지고 있습니다. 이런 특성으로 인해 무결성 검사에 자주 사용되며, 중간에서 데이터가 조작되었는지를 확인하는 데에 쓰입니다.

메인 함수에서는 "hello, world!"라는 문자열에 대한 해시를 생성하여 출력합니다. 이렇게 해시를 생성하고 검사하는 과정을 통해 데이터의 무결성을 확인할 수 있습니다.

그러나 이 예제 코드는 간단한 해시 생성의 예를 보여줄 뿐, 실제 네트워크 통신에서는 SSL/TLS와 같은 보안 프로토콜을 이용해야 합니다. 이러한 프로토콜은 데이터의 무결성뿐 아니라 기밀성, 인증 등을 모두 보장합니다.

보안은 네트워크 프로그래밍에서 빠질 수 없는 중요한 부분입니다. 인터넷의 발전에 따라 정보는 점점 더 많이 공유되고 있고, 이로 인해 보안 위협 또한 점점 더 증가하고 있습니다. 따라서 암호화, 인증, 무결성 검사 등 다양한 보안 기법을 이해하고 적용하는 것은 모든 개발자에게 중요한 역량입니다.