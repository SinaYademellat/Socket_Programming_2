#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4443

int main(int argc, char const *argv[]) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        std::cerr << "SSL_CTX_new failed\n";
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    connect(sock, (sockaddr*)&addr, sizeof(addr));

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "SSL connect failed\n";
        ERR_print_errors_fp(stderr);
    } else {
        
        std::cout << "Connected with SSL\n";        
        if(argc>=2){

            const char *Massage = argv[1];
            SSL_write(ssl, Massage, 24);
        }
        else{  
                SSL_write(ssl, "test from client (SSL)", 24);
        }
        char buf[1024] = {0};
        int len = SSL_read(ssl, buf, sizeof(buf));
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
    return 0;
}
