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
#include <util.h>

struct hostent *get_host_by_name(const char *url)
{
    struct hostent *host;
    char *valid_url;
    char *end = strchr(url, ':');

    if (!end)
        return gethostbyname(url);
    valid_url = strndup(url, strchr(url, ':') - url);
    host = gethostbyname(valid_url);
    if (host == NULL)
        return NULL;
    return host;
}

static int open_connection(const char *url)
{
    char *hostname = extract_hostname(url);
    struct hostent *server = get_host_by_name(hostname);
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
    if (connect(sockfd, (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    return sockfd;
}

static char *read_http_response(int sockfd)
{
    char *response = malloc(4096);
    ssize_t bytes_read;

    if (!response)
        return NULL;
    bytes_read = read(sockfd, response, 4095);
    if (bytes_read < 0) {
        free(response);
        return NULL;
    }
    response[bytes_read] = '\0';
    return response;
}

void append_config(char *request, request_config_t *config)
{
    char length[255];

    for (int i = 0; i < 10 && config->headers[i].key; i++) {
        strcat(request, config->headers[i].key);
        strcat(request, ": ");
        strcat(request, config->headers[i].value);
        strcat(request, "\r\n");
    }
    if (config->body) {
        snprintf(length, 255, "%ld", strlen(config->body));
        strcat(request, "Content-Length: ");
        strcat(request, length);
    }
    strcat(request, "\r\n\r\n");
    if (config->body) {
        strcat(request, config->body);
        strcat(request, "\r\n");
    }
}

response_t *check_response(int sockfd)
{
    char *response = read_http_response(sockfd);
    response_t *parsed_response;

    if (!response) {
        close(sockfd);
        return NULL;
    }
    parsed_response = parse_http_response(response);
    free(response);
    close(sockfd);
    return parsed_response;
}

response_t *fetch(const char *url, request_config_t *config)
{
    char *hostname = extract_hostname(url);
    char *path = extract_path(url);
    int sockfd = open_connection(hostname);
    char request[1024];

    if (sockfd < 0)
        return NULL;
    snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\n",
        method_to_string(config->method), path);
    append_config(request, config);
    if (write(sockfd, request, strlen(request)) < 0) {
        close(sockfd);
        return NULL;
    }
   return check_response(sockfd);
}
