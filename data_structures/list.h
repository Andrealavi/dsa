/* Node definition */
typedef struct Node Node;

struct Node {
    void* value;
    Node* next;
};

/* List definition */
typedef struct {
    Node* head;
    Node* tail;

    void (*copy)(void*, void*);
    int (*compare)(void*, void*);
} List;

/* Node methods */
Node* create_node(void* value, Node* next);
void destroy_node(Node* node);
void* node_get_value(Node* node);

/* List methods */
List* create_list(void* value, int (*compare_value)(void*, void*), void (*copy_value)(void*, void*));
void destroy_list(List* list);

List* list_append(List* list, void* value);
List* list_pop(List* list);

List* list_insert(List* list, void* value, int pos);
List* list_remove(List* list, int pos);

Node* list_find(List* list, void* value);

// List sort(List list);
