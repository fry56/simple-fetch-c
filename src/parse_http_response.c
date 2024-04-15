/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** parse_http_response
*/

#include <response.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *get_next_line(char **response)
{
    char *start = *response;
    char *end = strstr(start, "\r\n");

    if (end) {
        *end = '\0';
        *response = end + 2;
    }
    return start;
}

static response_t *init_response() {
    response_t *res = calloc(1, sizeof(response_t));

    if (!res)
        return NULL;
    res->headers = map_new();
    return res;
}

static bool parse_status_line(char **response, response_t *res) {
    char *line = get_next_line(response);

    return sscanf(line, "HTTP/%*s %d %[^\r\n]",
        &res->status_code, res->status_message) == 2;
}

static void parse_headers(char **response, response_t *res) {
    char *line;
    char *colon;

    while ((line = get_next_line(response)) && *line != '\0') {
        colon = strchr(line, ':');
        if (!colon)
            continue;
        *colon = '\0';
        map_add(res->headers, line, colon + 2);
    }
}

void free_response(response_t *response) {
    if (!response)
        return;
    if (response->status_message)
        free(response->status_message);
    if (response->headers) {
        for (map_node_t *node = response->headers->head; node; node = node->next) {
            free(node->key);
            free(node->value);
        }
        free(response->headers);
    }
    if (response->body)
        free(response->body);
    free(response);
}

response_t *parse_http_response(char *response)
{
    response_t *parsed_response;

    if (!response)
        return NULL;
    parsed_response = init_response();
    if (!parsed_response)
        return NULL;
    if (!parse_status_line(&response, parsed_response)) {
        free_response(parsed_response);
        return NULL;
    }
    parse_headers(&response, parsed_response);
    parsed_response->body = strdup(response);
    return parsed_response;
}
