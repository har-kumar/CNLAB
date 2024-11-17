#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
#define SERVER_IP "127.0.0.1"
int main() {
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    int server_len = sizeof(server_addr);
    int number, result;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &number);
    sendto(client_socket, (char*)&number, sizeof(int), 0, (struct sockaddr*)&server_addr, server_len);
    recvfrom(client_socket, (char*)&result, sizeof(int), 0, (struct sockaddr*)&server_addr, &server_len);
    printf("Factorial of %d is %d\n", number, result);
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
