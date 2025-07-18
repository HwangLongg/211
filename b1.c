#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char action;
    char value;
} Operation;

typedef struct {
    Operation data[1000];
    int top;
} Stack;

char text[1000];
int length = 0;

Stack undoStack;
Stack redoStack;

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, Operation op) {
    if (s->top < 999) {
        s->data[++(s->top)] = op;
    }
}

Operation pop(Stack *s) {
    Operation empty = {' ', ' '};
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return empty;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void insertChar(char x) {
    if (length < 999) {
        text[length++] = x;
        text[length] = '\0';
        Operation op = {'I', x};
        push(&undoStack, op);
        redoStack.top = -1;
    }
}

void undo() {
    if (!isEmpty(&undoStack)) {
        Operation lastOp = pop(&undoStack);
        if (lastOp.action == 'I' && length > 0 && text[length - 1] == lastOp.value) {
            length--;
            text[length] = '\0';
            push(&redoStack, lastOp);
        }
    } else {
        printf("Khong co thao tac de hoan tac.\n");
    }
}

void redo() {
    if (!isEmpty(&redoStack)) {
        Operation lastUndo = pop(&redoStack);
        if (lastUndo.action == 'I') {
            if (length < 999) {
                text[length++] = lastUndo.value;
                text[length] = '\0';
                push(&undoStack, lastUndo);
            }
        }
    } else {
        printf("Khong co thao tac de phuc hoi.\n");
    }
}

void displayText() {
    printf("Van ban hien tai: %s\n", text);
}

int main() {
    initStack(&undoStack);
    initStack(&redoStack);

    char command[20];
    char x;

    printf("—————— TEXT EDITOR ——————\n");

    while (1) {
        printf("\nNhap lenh (INSERT x | UNDO | REDO | HIEN THI | THOAT): ");
        scanf("%s", command);

        if (strcmp(command, "INSERT") == 0) {
            scanf(" %c", &x);
            insertChar(x);
        } else if (strcmp(command, "UNDO") == 0) {
            undo();
        } else if (strcmp(command, "REDO") == 0) {
            redo();
        } else if (strcmp(command, "HIEN") == 0) {
            scanf("%s", command);
            displayText();
        } else if (strcmp(command, "THOAT") == 0) {
            break;
        } else {
            printf("Lenh khong hop le.\n");
        }
    }

    return 0;
}
