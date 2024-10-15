#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int size;
} StaticList;

typedef struct {
    int data[MAX];
    int top;
} StaticStack;

typedef struct {
    int data[MAX];
    int front, rear;
} StaticQueue;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} DynamicList;

typedef struct {
    Node* top;
} DynamicStack;

typedef struct {
    Node* front;
    Node* rear;
} DynamicQueue;

void initStaticList(StaticList* list) {
    list->size = 0;
}

bool addStatic(StaticList* list, int value) {
    if (list->size < MAX) {
        list->data[list->size++] = value;
        return true;
    }
    return false;
}

bool removeStatic(StaticList* list, int value) {
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->size--;
            return true;
        }
    }
    return false;
}

void printStaticList(StaticList* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

void initStaticStack(StaticStack* stack) {
    stack->top = -1;
}

bool pushStatic(StaticStack* stack, int value) {
    if (stack->top < MAX - 1) {
        stack->data[++stack->top] = value;
        return true;
    }
    return false;
}

bool popStatic(StaticStack* stack, int* value) {
    if (stack->top >= 0) {
        *value = stack->data[stack->top--];
        return true;
    }
    return false;
}

void initStaticQueue(StaticQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
}

bool enqueueStatic(StaticQueue* queue, int value) {
    if (queue->rear < MAX - 1) {
        queue->data[++queue->rear] = value;
        return true;
    }
    return false;
}

bool dequeueStatic(StaticQueue* queue, int* value) {
    if (queue->front <= queue->rear) {
        *value = queue->data[queue->front++];
        return true;
    }
    return false;
}

void initDynamicList(DynamicList* list) {
    list->head = NULL;
}

bool addDynamic(DynamicList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false;
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    return true;
}

bool removeDynamic(DynamicList* list, int value) {
    Node *current = list->head, *prev = NULL;
    while (current) {
        if (current->data == value) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void printDynamicList(DynamicList* list) {
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void initDynamicStack(DynamicStack* stack) {
    stack->top = NULL;
}

bool pushDynamic(DynamicStack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false;
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    return true;
}

bool popDynamic(DynamicStack* stack, int* value) {
    if (stack->top) {
        Node* temp = stack->top;
        *value = temp->data;
        stack->top = stack->top->next;
        free(temp);
        return true;
    }
    return false;
}

void initDynamicQueue(DynamicQueue* queue) {
    queue->front = queue->rear = NULL;
}

bool enqueueDynamic(DynamicQueue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false;
    newNode->data = value;
    newNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newNode;
    } else {
        queue->front = newNode;
    }
    queue->rear = newNode;
    return true;
}

bool dequeueDynamic(DynamicQueue* queue, int* value) {
    if (queue->front) {
        Node* temp = queue->front;
        *value = temp->data;
        queue->front = queue->front->next;
        if (!queue->front) {
            queue->rear = NULL;
        }
        free(temp);
        return true;
    }
    return false;
}

int main() {
    int choice, value;
    printf("Escolha a estrutura (1: Estática, 2: Dinâmica): ");
    scanf("%d", &choice);

    if (choice == 1) {
        StaticList sList;
        StaticStack sStack;
        StaticQueue sQueue;
        initStaticList(&sList);
        initStaticStack(&sStack);
        initStaticQueue(&sQueue);


        addStatic(&sList, 10);
        addStatic(&sList, 20);
        printStaticList(&sList);

        pushStatic(&sStack, 30);
        pushStatic(&sStack, 40);
        popStatic(&sStack, &value);
        printf("Popped from stack: %d\n", value);

        enqueueStatic(&sQueue, 50);
        enqueueStatic(&sQueue, 60);
        dequeueStatic(&sQueue, &value);
        printf("Dequeued from queue: %d\n", value);

    } else if (choice == 2) {
        
        DynamicList dList;
        DynamicStack dStack;
        DynamicQueue dQueue;
        initDynamicList(&dList);
        initDynamicStack(&dStack);
        initDynamicQueue(&dQueue);

       
        addDynamic(&dList, 10);
        addDynamic(&dList, 20);
        printDynamicList(&dList);

        pushDynamic(&dStack, 30);
        pushDynamic(&dStack, 40);
        popDynamic(&dStack, &value);
        printf("Popped from stack: %d\n", value);

        enqueueDynamic(&dQueue, 50);
        enqueueDynamic(&dQueue, 60);
        dequeueDynamic(&dQueue, &value);
        printf("Dequeued from queue: %d\n", value);
    } else {
        printf("Escolha inválida.\n");
    }

    return 0;
}
