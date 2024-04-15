/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** request
*/

#pragma once

#include <map.h>
#include <method.h>
#include <response.h>

typedef struct request_header_s {
    char *key;
    char *value;
} request_header_t;

typedef struct request_config_s {
    method_t method;
    request_header_t headers[10];
    char *body;
} request_config_t;

response_t *fetch(const char *url, request_config_t *config);
