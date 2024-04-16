/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** utils
*/

#pragma once

#include <method.h>

const char *method_to_string(method_t method);
int extract_port(const char *url);
char *extract_hostname(const char *url);
char *extract_path(const char *url);
