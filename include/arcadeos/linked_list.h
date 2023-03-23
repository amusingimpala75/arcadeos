#pragma once

#include "stddef.h"

typedef struct linked_list linked_list_t;
typedef struct linked_list_node linked_list_node_t;

#define LINKED_LIST_HEADER(name, contents)                                     \
  typedef struct name##_node {                                                 \
    struct name##_node *prev;                                                  \
    struct name##_node *next;                                                  \
    contents                                                                   \
  } name##_node_t;                                                             \
  typedef struct name {                                                        \
    name##_node_t *first;                                                      \
    name##_node_t *last;                                                       \
    size_t count;                                                              \
  } name##_t;                                                                  \
  void name##_new(name##_t *list);                                             \
  name##_node_t *name##_add(name##_t *list);                                   \
  void name##_delete(name##_t *list);                                          \
  void name##_remove(name##_t *list, name##_node_t *node);                     \
  name##_node_t *name##_get(name##_t *list, size_t index);

#define LINKED_LIST_SOURCE(name)                                               \
  void name##_new(name##_t *list) { linked_list_new(list); }                   \
  name##_node_t *name##_add(name##_t *list) {                                  \
    return linked_list_add(list, sizeof(name##_node_t));                       \
  }                                                                            \
  void name##_delete(name##_t *list) { linked_list_delete(list); }             \
  void name##_remove(name##_t *list, name##_node_t *node) {                    \
    linked_list_remove(list, node);                                            \
  }                                                                            \
  name##_node_t *name##_get(name##_t *list, size_t index) {                    \
    return linked_list_get(list, index);                                       \
  }

#define LINKED_LIST(value) ((linked_list *)value)

void linked_list_new(linked_list_t *list);
linked_list_node_t *linked_list_add(linked_list_t *list, size_t node_size);
void linked_list_delete(linked_list_t *list);
void linked_list_remove(linked_list_t *list, linked_list_node_t *node);
linked_list_node_t *linked_list_get(linked_list_t *list, size_t index);
