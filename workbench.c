# include <stdio.h>
# include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;


void list_print(const Node *head);// function prototype

Node *list_push_front(Node *head, int v)
{
    Node *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc");
        exit(1);
    }

    new_node->value = v;
    new_node->next = head;
    return new_node;
}



int main(void)
{
    int x = 42;
    int *p = &x;
    printf("&x = %p\n", (void*)&x);
    printf("p = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    Node a = {1, NULL};
    Node b = {2, &a};
    printf("b.value = %d\n", b.value);
    printf("b.next->value = %d\n", b.next->value);

    Node *c = malloc(sizeof *c);
    c->value = 3;
    c->next = &b;
    printf("c->value = %d\n", c->value);
    printf("c->next->value = %d\n", c->next->value);
    printf("c->next->next->value = %d\n", c->next->next->value);
    list_print(c);

    Node *head = NULL;
    head = list_push_front(head, 1);
    head = list_push_front(head, 2);
    head = list_push_front(head, 3);
    list_print(head);



    free(c);

   

    

    return 0;
    

    
}

void list_print(const Node *head)
{
    const Node *current = head;
    while (current != NULL){
        printf("%d -> ", current->value);
        current = current->next;    
    }
}
    


