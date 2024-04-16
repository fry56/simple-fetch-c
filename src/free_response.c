/*
** EPITECH PROJECT, 2024
** bac-a-sable
** File description:
** free_response
*/

#include <response.h>

void free_response(response_t *response)
{
    if (!response)
        return;
    if (response->status_message)
        free(response->status_message);
    if (response->headers) {
        for (map_node_t *node = response->headers->head;
             node; node = node->next) {
            free(node->key);
            free(node->value);
        }
        free(response->headers);
    }
    if (response->body)
        free(response->body);
    free(response);
}
