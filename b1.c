#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Question {
    int id;
    char content[256];
} Question;

typedef struct StackNode {
    Question data;
    struct StackNode *next;
} StackNode;

typedef struct QueueNode {
    Question data;
    struct QueueNode *next;
} QueueNode;

StackNode *practiceStack = NULL;
StackNode *redoStack = NULL;
QueueNode *historyFront = NULL;
QueueNode *historyRear = NULL;

StackNode* createStackNode(Question q) {
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    node->data = q;
    node->next = NULL;
    return node;
}

QueueNode* createQueueNode(Question q) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = q;
    node->next = NULL;
    return node;
}

void push(StackNode **top, Question q) {
    StackNode *node = createStackNode(q);
    node->next = *top;
    *top = node;
}

int pop(StackNode **top, Question *q) {
    if (*top == NULL) return 0;
    StackNode *temp = *top;
    *q = temp->data;
    *top = (*top)->next;
    free(temp);
    return 1;
}

void enqueue(Question q) {
    QueueNode *node = createQueueNode(q);
    if (!historyRear) {
        historyFront = historyRear = node;
    } else {
        historyRear->next = node;
        historyRear = node;
    }
}

void displayHistory() {
    QueueNode *cur = historyFront;
    if (!cur) {
        printf("Khong co cau hoi trong lich su.\n");
        return;
    }
    while (cur) {
        printf("ID: %d | Content: %s\n", cur->data.id, cur->data.content);
        cur = cur->next;
    }
}

void practice() {
    Question q;
    printf("Nhap ID: ");
    scanf("%d", &q.id);
    getchar();
    printf("Nhap noi dung: ");
    fgets(q.content, sizeof(q.content), stdin);
    q.content[strcspn(q.content, "\n")] = '\0';

    push(&practiceStack, q);
    enqueue(q);
    printf("Da luyen cau hoi.\n");
}

void undo() {
    Question q;
    if (pop(&practiceStack, &q)) {
        push(&redoStack, q);
        printf("Da undo cau hoi: %s\n", q.content);
    } else {
        printf("Khong co cau hoi de undo.\n");
    }
}

void redo() {
    Question q;
    if (pop(&redoStack, &q)) {
        push(&practiceStack, q);
        printf("Da redo cau hoi: %s\n", q.content);
    } else {
        printf("Khong co cau hoi de redo.\n");
    }
}

void menu() {
    int choice;
    do {
        printf("\n————————— INTERVIEW MANAGER —————————\n");
        printf("1. PRACTICE: Luyen mot cau hoi moi\n");
        printf("2. UNDO: Bo qua cau hoi vua luyen\n");
        printf("3. REDO: Luyen lai cau hoi vua undo\n");
        printf("4. HISTORY: Hien thi lich su da luyen\n");
        printf("5. EXIT\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: practice(); break;
            case 2: undo(); break;
            case 3: redo(); break;
            case 4: displayHistory(); break;
            case 5: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
