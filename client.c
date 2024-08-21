#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include<unistd.h>

#define PORT 8080
#define LOG_FILE "client_log.txt"

void log_operation(const char *operation, const char *result) {
    FILE *log = fopen(LOG_FILE, "a");
    time_t now = time(NULL);
    fprintf(log, "%s - Operation: %s, Result: %s\n", ctime(&now), operation, result);
    fclose(log);
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char expression[1024] = {0};
    char result[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Enter arithmetic expression: ");
    fgets(expression, 1024, stdin);
    send(sock, expression, strlen(expression), 0);
    read(sock, result, 1024);
    printf("Result: %s\n", result);

    log_operation(expression, result);

    close(sock);
    return 0;
}
