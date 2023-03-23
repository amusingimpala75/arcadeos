#include "arcadeos/linked_list.h"
#include "stdlib.h"

struct linked_list {
  linked_list_node_t *first;
  linked_list_node_t *last;
  size_t count;
};

struct linked_list_node {
  linked_list_node_t *prev;
  linked_list_node_t *next;
};

void linked_list_new(linked_list_t *list) {
  list->first = NULL;
  list->last = NULL;
  list->count = 0;
}

void linked_list_delete(linked_list_t *list) {
  linked_list_node_t *node = list->first;
  for (;;) {
    if (node != NULL) {
      node = node->next;
      free(node->prev);
    } else
      break;
  }
}

linked_list_node_t *linked_list_add(linked_list_t *list, size_t node_size) {
  linked_list_node_t *node = malloc(node_size);
  if (node == NULL)
    return NULL;
  node->prev = list->last;
  node->next = NULL;
  list->count++;
  list->last = node;
  return node;
}

void linked_list_remove(linked_list_t *list, linked_list_node_t *node) {
  if (node == list->first)
    list->first = node->next;
  if (node == list->last)
    list->last = node->prev;
  if (node->prev != NULL)
    node->prev->next = node->next;
  if (node->next != NULL)
    node->next->prev = node->prev;
  free(node);
  list->count--;
}

linked_list_node_t *linked_list_get(linked_list_t *list, size_t index) {
  if (index + 1 >= list->count)
    return NULL;
  linked_list_node_t *node = list->first;
  for (size_t i = 0; i < index; i++)
    node = node->next;
  return node;
}
