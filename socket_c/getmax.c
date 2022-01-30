#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
 
#define MAX_SOCK 1024 // 솔라리스의 경우 64
 
int extern listen_sock;                 // 서버의 리슨 소켓
int extern num_user;
int extern clisock_list[MAX_SOCK];              // 채팅에 참가자 소켓번호 목록
 
 
// 최대 소켓번호 찾기
int getmax() {
        // Minimum 소켓번호는 가정 먼저 생성된 listen_sock
        int max = listen_sock;
        int i;
        for (i = 0; i < num_user; i++)
                if (clisock_list[i] > max)
                        max = clisock_list[i];
        return max;
}
