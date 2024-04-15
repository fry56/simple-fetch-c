/*
** EPITECH PROJECT, 2024
** http-standard-c
** File description:
** method
*/

#pragma once

#include <string.h>

typedef enum method_e {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
    INVALID_METHOD = 0
} method_t;

typedef struct {
    method_t method;
    const char *string;
} method_info_t;

static method_info_t methods[] __attribute__((unused)) = {
    {GET, "GET"},
    {POST, "POST"},
    {PUT, "PUT"},
    {DELETE, "DELETE"},
    {HEAD, "HEAD"},
    {CONNECT, "CONNECT"},
    {OPTIONS, "OPTIONS"},
    {TRACE, "TRACE"},
    {PATCH, "PATCH"},
    {0, NULL}
};
