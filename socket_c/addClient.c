#include "thread_function.h"
#include "addclient.h"
#include "removeclient.h"
#include "getmax.h"
#include "tcp_listen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define MAX_SOCK 1024 // 솔라리스의 경우 64
 
int extern num_user;                    // 채팅 참가자 수
int extern clisock_list[MAX_SOCK];              // 채팅에 참가자 소켓번호 목록
char extern ip_list[MAX_SOCK][20];
 
// 새로운 채팅 참가자 처리
void addClient(int s, struct sockaddr_in *newcliaddr) {
        char buf[20];
        inet_ntop(AF_INET, &newcliaddr->sin_addr, buf, sizeof(buf));
        write(1, "\033[0G", 4);         //커서의 X좌표를 0으로 이동
        fprintf(stderr, "\033[33m");    //글자색을 노란색으로 변경
        printf("new client: %s\n", buf);//ip출력
        // 채팅 클라이언트 목록에 추가
        clisock_list[num_user] = s;
        strcpy(ip_list[num_user], buf);
        num_user++; //유저 수 증가
}
