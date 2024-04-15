/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** response
*/

#pragma once

#include <map.h>

typedef struct response_s {
    int status_code;
    char *status_message;
    map_t *headers;
    char *body;
} response_t;

response_t *parse_http_response(char *response);
void free_response(response_t *response);
