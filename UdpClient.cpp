#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    const char *message = "Hello from UDP Client";
    struct sockaddr_in servaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Address configuration
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Send message to server
    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    std::cout << "Message sent to server\n";

    // Receive response from server
    int len, n;
    len = sizeof(servaddr);
    n = recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&servaddr, (socklen_t *)&len);
    buffer[n] = '\0';
    std::cout << "Message from server: " << buffer << "\n";

    // Close socket
    close(sockfd);
    return 0;
}
