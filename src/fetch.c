/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** fetch_new
*/

#include <request.h>
#include <response.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

const char *method_to_string(method_t method)
{
    for (int i = 0; methods[i].string; ++i) {
        if (methods[i].method == method)
            return methods[i].string;
    }
    return NULL;
}

static int extract_port(const char *url) {
    const char *port_str = strrchr(url, ':');

    if (port_str)
        return atoi(port_str + 1);
    return 80;
}

static int open_connection(const char *hostname)
{
    struct hostent *server = gethostbyname(hostname);
    int port = extract_port(hostname);
    struct sockaddr_in serv_addr = {0};
    int sockfd;

    if (!server)
        return -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return -1;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    return sockfd;
}

static char *read_http_response(int sockfd) {
    char *response = malloc(4096);
    ssize_t bytes_read;
    if (!response) return NULL;

    bytes_read = read(sockfd, response, 4095);
    if (bytes_read < 0) {
        free(response);
        return NULL;
    }
    response[bytes_read] = '\0';
    return response;
}

response_t *fetch(const char *url, request_config_t *config)
{
    int sockfd = open_connection(url);
    char request[1024], *response;
    response_t *parsed_response;

    if (sockfd < 0) return NULL;
    sprintf(request, "%s / HTTP/1.1\r\nHost: example.com\r\n", method_to_string(config->method));
    if (write(sockfd, request, strlen(request)) < 0) {
        close(sockfd);
        return NULL;
    }
    response = read_http_response(sockfd);
    if (!response) {
        close(sockfd);
        return NULL;
    }
    parsed_response = parse_http_response(response);
    free(response);
    close(sockfd);
    return parsed_response;
}
