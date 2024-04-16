/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** utils
*/

#include <stdlib.h>
#include <string.h>
#include <method.h>

const char *method_to_string(method_t method)
{
    for (int i = 0; methods[i].string; ++i) {
        if (methods[i].method == method)
            return methods[i].string;
    }
    return NULL;
}

int extract_port(const char *url)
{
    const char *port_str = strrchr(url, ':');

    if (port_str)
        return atoi(port_str + 1);
    return 80;
}

char *extract_hostname(const char *url)
{
    const char *start = strstr(url, "://");
    const char *end;
    char *result;
    size_t len;

    start = start ? start + 3 : url;
    end = strchr(start, '/');
    if (!end)
        end = start + strlen(start);
    len = end - start;
    result = malloc(len + 1);
    if (!result)
        return NULL;
    memcpy(result, start, len);
    result[len] = '\0';
    return result;
}

char *extract_path(const char *url)
{
    const char *start = strstr(url, "://");
    const char *end;

    start = start ? start + 3 : url;
    end = strchr(start, '/');
    if (!end)
        return strdup("/");
    return strdup(end);
}
