#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    const char *message = "Hello from UDP Server";
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Address configuration
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    int len, n;
    len = sizeof(cliaddr);
    std::cout << "UDP Server is waiting on port " << PORT << "...\n";

    // Receive data from client
    n = recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
    buffer[n] = '\0';
    std::cout << "Message from client: " << buffer << "\n";

    // Send response
    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    std::cout << "Message sent to client\n";

    // Close socket
    close(sockfd);
    return 0;
}
