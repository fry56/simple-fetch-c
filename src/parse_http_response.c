/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** parse_http_response
*/

#include <response.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

static response_t *init_response(void)
{
    response_t *res = calloc(1, sizeof(response_t));

    if (!res)
        return NULL;
    res->headers = map_new();
    return res;
}

static bool check_status_line(response_t *res, char *reason_phrase,
    int status_code)
{
    if (!reason_phrase)
        return false;
    res->status_code = status_code;
    res->status_message = reason_phrase;
    return true;
}

static bool parse_status_line(char **response, response_t *res)
{
    char *line = get_next_line(response);
    char *token;
    int status_code;
    char *reason_phrase;

    if (!line || strncmp(line, "HTTP/", 5) != 0)
        return false;
    token = strchr(line, ' ');
    if (!token)
        return false;
    token++;
    status_code = atoi(token);
    if (status_code == 0)
        return false;
    while (*token && isdigit(*token)) token++;
    while (*token && isspace(*token)) token++;
    reason_phrase = strdup(token);
    return check_status_line(res, reason_phrase, status_code);
}

static void parse_headers(char **response, response_t *res)
{
    char *line;
    char *colon;

    while ((line = get_next_line(response)) && *line != '\0') {
        colon = strchr(line, ':');
        if (!colon)
            continue;
        *colon = '\0';
        map_add(res->headers, strdup(line), strdup(colon + 2));
    }
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
        response_free(parsed_response);
        return NULL;
    }
    parse_headers(&response, parsed_response);
    parsed_response->body = strdup(response);
    return parsed_response;
}
