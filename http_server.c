#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

// Function to parse the "name" parameter from the query string
char* get_name_from_request(const char* request) {
    char* name = NULL;
    char* query_start = strstr(request, "GET /?name=");  // Find the start of "?name="
    if (query_start) {
        query_start += strlen("GET /?name=");  // Move pointer to the start of the name value
        char* query_end = strchr(query_start, ' ');  // Find the end of the query (space after the name)
        if (query_end) {
            size_t name_length = query_end - query_start;
            name = (char*)malloc(name_length + 1);
            strncpy(name, query_start, name_length);
            name[name_length] = '\0';  // Null-terminate the name string
        }
    }
    return name;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char default_message[] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nHello world";
    
    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind socket to port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 4. Accept connections
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // 5. Read HTTP request
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received request: %s\n", buffer);

        // 6. Parse "name" from request
        char* name = get_name_from_request(buffer);
        
        char response[BUFFER_SIZE];
        if (name) {
            // Prepare custom message "Hello <name>"
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: %ld\n\nHello %s",
                     strlen(name) + 7, name);  // Length of "Hello " + name length
            free(name);  // Free the allocated memory for the name
        } else {
            // Default message if no "name" parameter
            strncpy(response, default_message, sizeof(default_message));
        }

        // 7. Send the HTTP response
        send(new_socket, response, strlen(response), 0);
        printf("Response sent\n");

        // 8. Close the connection
        close(new_socket);
    }

    close(server_fd);
    return 0;
}