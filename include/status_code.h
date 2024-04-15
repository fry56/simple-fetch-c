/*
** EPITECH PROJECT, 2024
** http-standard-c
** File description:
** status_code
*/

#pragma once

#include <stddef.h>

typedef enum status_code_e {
    NOT_FOUND = 404,
    OK = 200,
    CREATED = 201,
    NO_CONTENT = 204,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    CONFLICT = 409,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    SERVICE_UNAVAILABLE = 503,
    INVALID_CODE = 0
} status_code_t;

typedef struct {
    status_code_t code;
    const char *message;
} status_code_info_t;

static status_code_info_t status_codes[] __attribute__((unused)) = {
    {OK, "OK"},
    {CREATED, "Created"},
    {NO_CONTENT, "No Content"},
    {BAD_REQUEST, "Bad Request"},
    {UNAUTHORIZED, "Unauthorized"},
    {FORBIDDEN, "Forbidden"},
    {CONFLICT, "Conflict"},
    {NOT_FOUND, "Not Found"},
    {INTERNAL_SERVER_ERROR, "Internal Server Error"},
    {NOT_IMPLEMENTED, "Not Implemented"},
    {SERVICE_UNAVAILABLE, "Service Unavailable"},
    {0, NULL}
};
