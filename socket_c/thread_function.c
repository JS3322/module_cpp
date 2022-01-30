#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <pthread.h>
 
#define MAXLINE  511
#define MAX_SOCK 1024 // 솔라리스의 경우 64
 
int num_user = 0;
int num_chat = 0;
char ip_list[MAX_SOCK][20];
 
void *thread_function(void *arg) { //명령어를 처리할 스레드
        int i;
        printf("명령어 목록 : help, num_user, num_chat, ip_list\n");
        while (1) {
                char bufmsg[MAXLINE + 1];
                fprintf(stderr, "\033[1;32m"); //글자색을 녹색으로 변경
                printf("server>"); //커서 출력
                fgets(bufmsg, MAXLINE, stdin); //명령어 입력
                if (!strcmp(bufmsg, "\n")) continue;   //엔터 무시
                else if (!strcmp(bufmsg, "help\n"))    //명령어 처리
                        printf("help, num_user, num_chat, ip_list\n");
                else if (!strcmp(bufmsg, "num_user\n"))//명령어 처리
                        printf("현재 참가자 수 = %d\n", num_user);
                else if (!strcmp(bufmsg, "num_chat\n"))//명령어 처리
                        printf("지금까지 오간 대화의 수 = %d\n", num_chat);
                else if (!strcmp(bufmsg, "ip_list\n")) //명령어 처리
                        for (i = 0; i < num_user; i++)
                                printf("%s\n", ip_list[i]);
                else //예외 처리
                        printf("해당 명령어가 없습니다.help를 참조하세요.\n");
        }
}
