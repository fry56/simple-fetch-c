/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** response
*/

#pragma once

#include <map.h>
#include <status_code.h>

typedef struct response_s {
    status_code_t status_code;
    char *status_message;
    map_t *headers;
    char *body;
} response_t;

response_t *parse_http_response(char *response);
void response_free(response_t *response);
