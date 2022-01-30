#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


DWORD WINAPI SendThread( LPVOID lpData );

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // 소켓 라이브러리 초기화
    WSADATA wsaData;
    int token = WSAStartup( WINSOCK_VERSION, &wsaData );

    // 소켓 생성
    SOCKET socket_client = socket( PF_INET, SOCK_STREAM, 0 );

    // 소켓 주소 정보
    SOCKADDR_IN servAddr={0};
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr( "192.168.0.2" );
    servAddr.sin_port=htons( 9000 ); // 테스트용 포트

    // 소켓 접속
    if( connect( socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr) ) == SOCKET_ERROR )
    {
        closesocket( socket_client );
       // MessageBox( NULL, _T("서버에 접속 할수 없습니다."), NULL, MB_OK );
        return SOCKET_ERROR;
    }

    // 콘솔창 생성
    AllocConsole();

    CreateThread( NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL );

    // 상태 출력
    DWORD dwTmp;
    char text[1024] = "서버에 접속되었습니다.\n";
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text) , &dwTmp, NULL);

    // 전송 & 수신 루푸
    while( 1 )
    {
        char buffer[1024]={0};
        int len = recv( socket_client, buffer, sizeof(buffer), 0 );
        if ( len <= 0 )
        {
           // MessageBox( NULL, _T("접속이 종료 되었습니다."), NULL, MB_OK );
            break;
        }

        // 메시지 출력
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer) , &dwTmp, NULL);
    }

    //소켓 해제
    closesocket( socket_client );

    // 콘솔 창 제거
    FreeConsole();

    return 0;
}

DWORD WINAPI SendThread( LPVOID lpData )
{
    SOCKET socket_client = (SOCKET)lpData;
    while( 1 )
    {
        DWORD dwTmp;
        char text[1024]={0};
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), text, 1024 , &dwTmp, NULL);

        // 문자열 전송
        send( socket_client, text, strlen(text), 0 );
    }
    return 0;
}