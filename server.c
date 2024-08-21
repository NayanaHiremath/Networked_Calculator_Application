#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define PORT 8080
#define LOG_FILE "server_log.txt"

void log_request(const char *client_ip, const char *expression, const char *result, double time_taken, size_t data_size) {
    FILE *log = fopen(LOG_FILE, "a");
    time_t now = time(NULL);
    fprintf(log, "%s - Client: %s, Expression: %s, Result: %s, Time Taken: %.6f seconds, Data Size: %zu bytes\n", 
            ctime(&now), client_ip, expression, result, time_taken, data_size);
    fclose(log);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char result[1024];

    struct timespec start, end;
    double time_taken;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) >= 0) {
        clock_gettime(CLOCK_MONOTONIC, &start); 
        
        read(new_socket, buffer, 1024);

       
        int num1, num2;
        char operator;
        int parsed_items = sscanf(buffer, "%d %c %d", &num1, &operator, &num2);

        if (parsed_items != 3) {
            strcpy(result, "Error: Invalid expression format");
        } else {
            switch (operator) {
                case '+': sprintf(result, "%d", num1 + num2); break;
                case '-': sprintf(result, "%d", num1 - num2); break;
                case '*': sprintf(result, "%d", num1 * num2); break;
                case '/': 
                    if (num2 == 0) {
                        strcpy(result, "Error: Division by zero");
                    } else {
                        sprintf(result, "%d", num1 / num2);
                    }
                    break;
                case '%': 
                    if (num2 == 0) {
                        strcpy(result, "Error: Modulus by zero");
                    } else {
                        sprintf(result, "%d", num1 % num2);
                    }
                    break;
                case '^': 
                    sprintf(result, "%d", (int)pow(num1, num2));  
                    break;
                default: 
                    strcpy(result, "Error: Invalid operator");
                    break;
            }
        }

        size_t data_size = strlen(result);
        send(new_socket, result, data_size, 0);
        
        clock_gettime(CLOCK_MONOTONIC, &end); 
        
       
        time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        log_request(inet_ntoa(address.sin_addr), buffer, result, time_taken, data_size);
        
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
