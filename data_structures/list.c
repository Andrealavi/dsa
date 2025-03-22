#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* Node methods */
Node* create_node(void* value, Node* next) {
    Node* node = (struct Node*) malloc(sizeof(struct Node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->next = next;

    return node;
};

void* get_value(Node* node) {
    return node->value;
};

void destroy_node(Node* node) {
    if (node != NULL) {
        if (node->value != NULL) {
            free(node->value);
        }

        free(node);
    }
}

/* List methods */
List* create_list(void *value, int (*compare_value)(void *, void *), void (*copy_value)(void*, void *)) {
    List* list = (List*) malloc(sizeof(List));

    if (list == NULL) {
        return NULL;
    }

    Node* node = create_node(value, NULL);

    list->head = node;
    list->tail = node;

    list->copy = copy_value;
    list->compare = compare_value;

    return list;
};

void destroy_list(List* list) {
    if (list != NULL) {
        Node* head = list->head;

        while (head != NULL) {
            Node* node = head;
            head = head->next;
            destroy_node(node);
        }
    }

    free(list);
};

List* list_append(List* list, void* value) {
    Node* node = create_node(value, NULL);

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;

    return list;
};

List* list_pop(List* list) {
    if (list->head == NULL) {
        return NULL;
    }

    Node* tail = list->tail;

    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        Node* element = list->head;

        while (element->next != tail) {
            element = element->next;
        }

        element->next = NULL;
        list->tail = element;
    }

    destroy_node(tail);

    return list;
}

List* list_insert(List* list, void* value, int pos) {
    Node* node = create_node(value, list->head);

    if (list->head == NULL && pos > 0) {
        return NULL;
    }

    if (pos == 0) {
        list->head = node;
    } else {
        int count = 0;
        Node* head = list->head;

        while (count < pos - 1 && head != NULL) {
            head = head->next;
            count++;
        }

        if (head == NULL) {
            return NULL;
        }

        node->next = head;
        head->next = node;
    }

    return list;
}

List* list_remove(List* list, int pos) {
    if (list->head == NULL) {
        return NULL;
    }

    Node* element = list->head;
    Node* node_to_remove;

    if (pos == 0) {
        list->head = element->next;

        if (element == list->tail) list->tail = NULL;

        node_to_remove = element;
    } else {
        int count = 0;

        while (element != NULL && count < pos - 1) {
            element = element->next;
            count++;
        }

        if (element == NULL) {
            return NULL;
        }

        Node* node_to_remove = element->next;
        element->next = element->next->next;
    }

    destroy_node(node_to_remove);

    return list;
}

Node* list_find(List* list, void* value) {
    Node* element = list->head;

    while (element != NULL) {
        if (list->compare(element->value, value) == 0) {
            return element;
        }

        element = element->next;
    }

    return NULL;
}
