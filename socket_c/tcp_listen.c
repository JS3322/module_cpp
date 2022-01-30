#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
 
 
// listen 소켓 생성 및 listen
int  tcp_listen(int host, int port, int backlog) {
        int sd;
        struct sockaddr_in servaddr;
 
        sd = socket(AF_INET, SOCK_STREAM, 0);
        if (sd == -1) {
                perror("socket fail");
                exit(1);
        }
        // servaddr 구조체의 내용 세팅
        bzero((char *)&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(host);
        servaddr.sin_port = htons(port);
        if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
                perror("bind fail");  exit(1);
        }
        // 클라이언트로부터 연결요청을 기다림
        listen(sd, backlog);
        return sd;
}
