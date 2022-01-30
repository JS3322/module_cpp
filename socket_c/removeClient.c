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
 
#define MAX_SOCK 1024 // 솔라리스의 경우 64
int extern num_user;                    // 채팅 참가자 수
int extern clisock_list[MAX_SOCK];              // 채팅에 참가자 소켓번호 목록
char extern ip_list[MAX_SOCK][20];              //접속한 ip목록
time_t extern ct;
struct tm extern tm;
 
// 채팅 탈퇴 처리
void removeClient(int s) {
        close(clisock_list[s]);
        if (s != num_user - 1) { //저장된 리스트 재배열
                clisock_list[s] = clisock_list[num_user - 1];
                strcpy(ip_list[s], ip_list[num_user - 1]);
        }
        num_user--; //유저 수 감소
        ct = time(NULL);                        //현재 시간을 받아옴
        tm = *localtime(&ct);
        write(1, "\033[0G", 4);         //커서의 X좌표를 0으로 이동
        fprintf(stderr, "\033[33m");//글자색을 노란색으로 변경
        printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("채팅 참가자 1명 탈퇴. 현재 참가자 수 = %d\n", num_user);
        fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
        fprintf(stderr, "server>"); //커서 출력
}
