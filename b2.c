#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[100];
    int priority;
    char deadline[20];
} Task;

typedef struct NodeSLL {
    Task data;
    struct NodeSLL* next;
} NodeSLL;

typedef struct NodeDLL {
    Task data;
    struct NodeDLL* prev;
    struct NodeDLL* next;
} NodeDLL;

NodeSLL* headSLL = NULL;
NodeDLL* headDLL = NULL;
NodeDLL* tailDLL = NULL;

void addTask() {
    Task t;
    printf("Nhap ID: "); scanf("%d", &t.id);
    getchar();
    printf("Nhap tieu de: "); fgets(t.title, sizeof(t.title), stdin); t.title[strcspn(t.title, "\n")] = '\0';
    printf("Nhap muc do uu tien: "); scanf("%d", &t.priority);
    getchar();
    printf("Nhap deadline: "); fgets(t.deadline, sizeof(t.deadline), stdin); t.deadline[strcspn(t.deadline, "\n")] = '\0';

    NodeSLL* newNode = (NodeSLL*)malloc(sizeof(NodeSLL));
    newNode->data = t;
    newNode->next = headSLL;
    headSLL = newNode;
    printf("Da them nhiem vu thanh cong.\n");
}

void displayTasks() {
    NodeSLL* cur = headSLL;
    if (!cur) {
        printf("Danh sach trong.\n");
        return;
    }
    printf("\n--- Danh sach nhiem vu ---\n");
    while (cur) {
        printf("ID: %d | Title: %s | Priority: %d | Deadline: %s\n", cur->data.id, cur->data.title, cur->data.priority, cur->data.deadline);
        cur = cur->next;
    }
}

void deleteTask() {
    int id;
    printf("Nhap ID can xoa: ");
    scanf("%d", &id);
    NodeSLL *cur = headSLL, *prev = NULL;

    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next;
            else headSLL = cur->next;
            free(cur);
            printf("Da xoa nhiem vu co ID %d.\n", id);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Khong tim thay nhiem vu co ID %d.\n", id);
}

void updateTask() {
    int id;
    printf("Nhap ID can cap nhat: ");
    scanf("%d", &id);
    getchar();
    NodeSLL* cur = headSLL;
    while (cur) {
        if (cur->data.id == id) {
            printf("Cap nhat tieu de moi: "); fgets(cur->data.title, sizeof(cur->data.title), stdin); cur->data.title[strcspn(cur->data.title, "\n")] = '\0';
            printf("Cap nhat muc do uu tien moi: "); scanf("%d", &cur->data.priority); getchar();
            printf("Cap nhat deadline moi: "); fgets(cur->data.deadline, sizeof(cur->data.deadline), stdin); cur->data.deadline[strcspn(cur->data.deadline, "\n")] = '\0';
            printf("Cap nhat thanh cong.\n");
            return;
        }
        cur = cur->next;
    }
    printf("Khong tim thay nhiem vu.\n");
}

void markTaskDone() {
    int id;
    printf("Nhap ID nhiem vu da hoan thanh: ");
    scanf("%d", &id);

    NodeSLL *cur = headSLL, *prev = NULL;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next;
            else headSLL = cur->next;

            NodeDLL* done = (NodeDLL*)malloc(sizeof(NodeDLL));
            done->data = cur->data;
            done->prev = tailDLL;
            done->next = NULL;
            if (tailDLL) tailDLL->next = done;
            else headDLL = done;
            tailDLL = done;

            free(cur);
            printf("Da danh dau hoan thanh nhiem vu.\n");
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Khong tim thay nhiem vu.\n");
}

void sortTasksByPriority() {
    if (!headSLL || !headSLL->next) return;
    int swapped;
    NodeSLL *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = headSLL;
        while (ptr1->next != lptr) {
            if (ptr1->data.priority > ptr1->next->data.priority) {
                Task temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Da sap xep nhiem vu theo do uu tien tang dan.\n");
}

void searchTaskByTitle() {
    char keyword[100];
    getchar();
    printf("Nhap tieu de can tim: "); fgets(keyword, sizeof(keyword), stdin); keyword[strcspn(keyword, "\n")] = '\0';

    NodeSLL* cur = headSLL;
    int found = 0;
    while (cur) {
        if (strstr(cur->data.title, keyword)) {
            printf("Tim thay - ID: %d | Title: %s | Priority: %d | Deadline: %s\n", cur->data.id, cur->data.title, cur->data.priority, cur->data.deadline);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) printf("Khong tim thay nhiem vu co tieu de chua \"%s\"\n", keyword);
}

void freeAll() {
    NodeSLL* curSLL = headSLL;
    while (curSLL) {
        NodeSLL* tmp = curSLL;
        curSLL = curSLL->next;
        free(tmp);
    }

    NodeDLL* curDLL = headDLL;
    while (curDLL) {
        NodeDLL* tmp = curDLL;
        curDLL = curDLL->next;
        free(tmp);
    }
}

int main() {
    int choice;
    do {
        printf("\n—————— TASK MANAGER ——————\n");
        printf("1. Them nhiem vu\n");
        printf("2. Hien thi danh sach nhiem vu\n");
        printf("3. Xoa nhiem vu\n");
        printf("4. Cap nhat thong tin nhiem vu\n");
        printf("5. Danh dau nhiem vu hoan thanh\n");
        printf("6. Sap xep nhiem vu theo uu tien\n");
        printf("7. Tim kiem nhiem vu theo tieu de\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: displayTasks(); break;
            case 3: deleteTask(); break;
            case 4: updateTask(); break;
            case 5: markTaskDone(); break;
            case 6: sortTasksByPriority(); break;
            case 7: searchTaskByTitle(); break;
            case 8: freeAll(); printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 8);
    return 0;
}
