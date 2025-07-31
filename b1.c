#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Command {
    char command[100];
    struct Command* next;
} Command;

Command* executedStack = NULL;
Command* redoStack = NULL;

void push(Command** stack, const char* cmd) {
    Command* newNode = (Command*)malloc(sizeof(Command));
    strcpy(newNode->command, cmd);
    newNode->next = *stack;
    *stack = newNode;
}

char* pop(Command** stack) {
    if (*stack == NULL) return NULL;
    Command* temp = *stack;
    *stack = temp->next;
    char* cmd = strdup(temp->command);
    free(temp);
    return cmd;
}

void clearStack(Command** stack) {
    while (*stack != NULL) {
        Command* temp = *stack;
        *stack = temp->next;
        free(temp);
    }
}

void printStack(Command* stack) {
    Command* temp = stack;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->command);
        temp = temp->next;
    }
}

void themLenhMoi() {
    char newCmd[100];
    printf("Nhap lenh moi: ");
    getchar();
    fgets(newCmd, sizeof(newCmd), stdin);
    newCmd[strcspn(newCmd, "\n")] = '\0';
    push(&executedStack, newCmd);
    clearStack(&redoStack);
    printf("Da them lenh moi: %s\n", newCmd);
}

void hoanTacLenh() {
    if (executedStack == NULL) {
        printf("Khong co lenh nao de hoan tac.\n");
        return;
    }
    char* undone = pop(&executedStack);
    push(&redoStack, undone);
    printf("Da hoan tac lenh: %s\n", undone);
    free(undone);
}

void phucHoiLenh() {
    if (redoStack == NULL) {
        printf("Khong co lenh nao de phuc hoi.\n");
        return;
    }
    char* redone = pop(&redoStack);
    push(&executedStack, redone);
    printf("Da phuc hoi lenh: %s\n", redone);
    free(redone);
}

void xemLenhHienTai() {
    if (executedStack == NULL) {
        printf("Khong co lenh nao dang duoc thuc hien.\n");
    } else {
        printf("Lenh hien tai: %s\n", executedStack->command);
    }
}

void danhSachLenhDaThucHien() {
    if (executedStack == NULL) {
        printf("Khong co lenh nao da duoc thuc hien.\n");
    } else {
        printf("Danh sach lenh da thuc hien:\n");
        printStack(executedStack);
    }
}

void lamMoiLichSu() {
    clearStack(&executedStack);
    clearStack(&redoStack);
    printf("Da lam moi lich su.\n");
}

void giaiPhongBoNho() {
    clearStack(&executedStack);
    clearStack(&redoStack);
}

int main() {
    int choice;
    do {
        printf("\n------------------ ROBOT COMMAND MANAGER ------------------\n");
        printf("1. THEM LENH MOI (MOVE, TURN, JUMP,...)\n");
        printf("2. HOAN TAC LENH (UNDO)\n");
        printf("3. PHUC HOI LENH (REDO)\n");
        printf("4. XEM LENH HIEN TAI\n");
        printf("5. DANH SACH LENH DA THUC HIEN\n");
        printf("6. LAM MOI LICH SU\n");
        printf("7. THOAT\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: themLenhMoi(); break;
            case 2: hoanTacLenh(); break;
            case 3: phucHoiLenh(); break;
            case 4: xemLenhHienTai(); break;
            case 5: danhSachLenhDaThucHien(); break;
            case 6: lamMoiLichSu(); break;
            case 7:
                giaiPhongBoNho();
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }

    } while (choice != 7);

    return 0;
}
