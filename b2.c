#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Cấu trúc cuộc gọi
typedef struct {
    char phone[20];
    char timeStr[30];
} Call;

// Cấu trúc Stack
typedef struct {
    Call data[MAX];
    int top;
} Stack;

// Cấu trúc Queue
typedef struct {
    Call data[MAX];
    int front, rear;
} Queue;

// ==== Stack Functions ====
void initStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, Call c) {
    if (!isFullStack(s)) {
        s->data[++s->top] = c;
    }
}

Call pop(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[s->top--];
    }
    Call empty = {"", ""};
    return empty;
}

Call peek(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[s->top];
    }
    Call empty = {"", ""};
    return empty;
}

// ==== Queue Functions ====
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isEmptyQueue(Queue *q) {
    return q->rear < q->front;
}

int isFullQueue(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, Call c) {
    if (!isFullQueue(q)) {
        q->data[++q->rear] = c;
    }
}

void displayQueue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("Lich su cuoc goi trong.\n");
        return;
    }
    printf("\nLich su cuoc goi:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("So: %s | Thoi gian: %s\n", q->data[i].phone, q->data[i].timeStr);
    }
}

// ==== Thời gian hiện tại ====
void getCurrentTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", t);
}

// ==== Main Program ====
int main() {
    Stack backStack, forwardStack;
    Queue callHistoryQueue;

    initStack(&backStack);
    initStack(&forwardStack);
    initQueue(&callHistoryQueue);

    int choice;
    do {
        printf("\n===== CALL HISTORY MANAGER =====\n");
        printf("1. CALL (Goi so moi)\n");
        printf("2. BACK (Quay lai so truoc)\n");
        printf("3. REDIAL (Goi lai so tiep theo)\n");
        printf("4. HISTORY (Xem lich su cuoc goi)\n");
        printf("5. EXIT (Thoat chuong trinh)\n");
        printf("Chon chuc nang (1-5): ");
        scanf("%d", &choice);
        getchar(); // Loại bỏ ký tự Enter

        if (choice == 1) {
            Call c;
            printf("Nhap so dien thoai: ");
            fgets(c.phone, 20, stdin);
            c.phone[strcspn(c.phone, "\n")] = '\0';  // Xóa newline
            getCurrentTime(c.timeStr);

            push(&backStack, c);           // Thêm vào back stack
            enqueue(&callHistoryQueue, c); // Thêm vào queue lịch sử
            initStack(&forwardStack);      // Reset forward stack

            printf("Da goi den: %s\n", c.phone);
        }
        else if (choice == 2) {
            if (backStack.top < 1) {
                printf("Khong co cuoc goi nao truoc do de quay lai.\n");
            } else {
                Call last = pop(&backStack);
                push(&forwardStack, last);
                Call current = peek(&backStack);
                printf("Da quay lai so: %s\n", current.phone);
            }
        }
        else if (choice == 3) {
            if (isEmptyStack(&forwardStack)) {
                printf("Khong co so nao de goi lai.\n");
            } else {
                Call redial = pop(&forwardStack);
                push(&backStack, redial);
                printf("Da goi lai so: %s\n", redial.phone);
            }
        }
        else if (choice == 4) {
            displayQueue(&callHistoryQueue);
        }
        else if (choice == 5) {
            printf("Dang thoat chuong trinh...\n");
        }
        else {
            printf("Lua chon khong hop le. Vui long nhap tu 1 den 5.\n");
        }

    } while (choice != 5);

    return 0;
}
