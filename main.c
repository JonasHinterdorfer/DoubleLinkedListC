#include <stddef.h>
#include <malloc.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

void print(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*
void insert_sorted(LinkedList* list, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;

    //when no value is in list
    if(list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    Node* currentNode = list->head;
    while (currentNode != NULL && currentNode->data < data)
        currentNode = currentNode->next;

    //when element is the biggest in list
    if(currentNode == NULL)
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        return;
    }

    if(currentNode == list->head)
    {
        newNode->next = list->head;
        newNode->next->prev = newNode;
        list->head = newNode;
        return;
    }

    newNode->prev = currentNode->prev;
    currentNode->prev->next = newNode;
    currentNode->prev = newNode;
    newNode->next = currentNode;

}*/

int insert_sorted(LinkedList* list,int data)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;

    if(list == NULL)
        return -1;
    if(list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return 1;
    }

    Node* currentNode = list->head;
    while (currentNode != NULL && currentNode->data < data)
        currentNode= currentNode->next;

    //to tail
    if(currentNode == NULL)
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        return 2;
    }

    if(currentNode == list->head)
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        return 3;
    }

    newNode->next = currentNode;
    newNode->prev = currentNode->prev;
    newNode->prev->next = newNode;

    return 4;
}
void deleteEverySecond(LinkedList* list)
{
    Node* current = list->head;
    while (current != NULL && current->next != NULL)
    {
        Node* toDelete = current->next;
        current->next = current->next->next;
        current->next->prev = current;
        free(toDelete);

        current = current->next;
    }
}

Node* getAt(LinkedList* list, int index)
{
    Node* current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}

void moveToFront(LinkedList* list, int index)
{
    Node* toMove = getAt(list, index);
    if(toMove == list->head)
        return;

    toMove->prev->next = toMove->next;
    toMove->next->prev = toMove->prev;
    toMove->next = list->head;
    list->head->prev = toMove;
    toMove->prev = NULL;

    list->head = toMove;
}

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void freeList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

int main()
{
    struct LinkedList* list = create_list();
    insert_sorted(list, 3);
    insert_sorted(list, 2);
    print(list);
    insert_sorted(list, 5);
    insert_sorted(list, 1);
    insert_sorted(list, 4);
    print(list);
    moveToFront(list, 2);
    print(list);
    deleteEverySecond(list);
    print(list);

    freeList(list);
}