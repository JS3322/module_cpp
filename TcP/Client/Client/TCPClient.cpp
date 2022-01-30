#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


DWORD WINAPI SendThread( LPVOID lpData );

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // ���� ���̺귯�� �ʱ�ȭ
    WSADATA wsaData;
    int token = WSAStartup( WINSOCK_VERSION, &wsaData );

    // ���� ����
    SOCKET socket_client = socket( PF_INET, SOCK_STREAM, 0 );

    // ���� �ּ� ����
    SOCKADDR_IN servAddr={0};
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr( "192.168.0.2" );
    servAddr.sin_port=htons( 9000 ); // �׽�Ʈ�� ��Ʈ

    // ���� ����
    if( connect( socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr) ) == SOCKET_ERROR )
    {
        closesocket( socket_client );
       // MessageBox( NULL, _T("������ ���� �Ҽ� �����ϴ�."), NULL, MB_OK );
        return SOCKET_ERROR;
    }

    // �ܼ�â ����
    AllocConsole();

    CreateThread( NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL );

    // ���� ���
    DWORD dwTmp;
    char text[1024] = "������ ���ӵǾ����ϴ�.\n";
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text) , &dwTmp, NULL);

    // ���� & ���� ��Ǫ
    while( 1 )
    {
        char buffer[1024]={0};
        int len = recv( socket_client, buffer, sizeof(buffer), 0 );
        if ( len <= 0 )
        {
           // MessageBox( NULL, _T("������ ���� �Ǿ����ϴ�."), NULL, MB_OK );
            break;
        }

        // �޽��� ���
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer) , &dwTmp, NULL);
    }

    //���� ����
    closesocket( socket_client );

    // �ܼ� â ����
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

        // ���ڿ� ����
        send( socket_client, text, strlen(text), 0 );
    }
    return 0;
}