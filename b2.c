#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Question {
    int id;
    char content[256];
    char topic[100];
    int level;
} Question;

typedef struct NodeSLL {
    Question data;
    struct NodeSLL *next;
} NodeSLL;

typedef struct NodeDLL {
    Question data;
    struct NodeDLL *prev;
    struct NodeDLL *next;
} NodeDLL;

NodeSLL *headSLL = NULL;
NodeDLL *headDLL = NULL;
NodeDLL *tailDLL = NULL;

NodeSLL* createNodeSLL(Question q) {
    NodeSLL *node = (NodeSLL*)malloc(sizeof(NodeSLL));
    node->data = q;
    node->next = NULL;
    return node;
}

NodeDLL* createNodeDLL(Question q) {
    NodeDLL *node = (NodeDLL*)malloc(sizeof(NodeDLL));
    node->data = q;
    node->prev = node->next = NULL;
    return node;
}

void addQuestion() {
    Question q;
    printf("Nhap ID: "); scanf("%d", &q.id);
    getchar();
    printf("Nhap noi dung: "); fgets(q.content, sizeof(q.content), stdin);
    q.content[strcspn(q.content, "\n")] = '\0';
    printf("Nhap chu de: "); fgets(q.topic, sizeof(q.topic), stdin);
    q.topic[strcspn(q.topic, "\n")] = '\0';
    printf("Nhap do kho (1-5): "); scanf("%d", &q.level);

    NodeSLL *node = createNodeSLL(q);
    node->next = headSLL;
    headSLL = node;

    printf("Them cau hoi thanh cong.\n");
}

void displaySLL() {
    NodeSLL *cur = headSLL;
    if (!cur) {
        printf("Khong co cau hoi dang luyen.\n");
        return;
    }
    while (cur) {
        printf("ID: %d | Content: %s | Topic: %s | Level: %d\n", 
               cur->data.id, cur->data.content, cur->data.topic, cur->data.level);
        cur = cur->next;
    }
}

void updateQuestion() {
    int id;
    printf("Nhap ID cau hoi can cap nhat: ");
    scanf("%d", &id);
    getchar();
    NodeSLL *cur = headSLL;
    while (cur) {
        if (cur->data.id == id) {
            printf("Cap nhat noi dung moi: "); fgets(cur->data.content, sizeof(cur->data.content), stdin);
            cur->data.content[strcspn(cur->data.content, "\n")] = '\0';
            printf("Cap nhat chu de moi: "); fgets(cur->data.topic, sizeof(cur->data.topic), stdin);
            cur->data.topic[strcspn(cur->data.topic, "\n")] = '\0';
            printf("Cap nhat do kho moi (1-5): "); scanf("%d", &cur->data.level);
            printf("Cap nhat thanh cong.\n");
            return;
        }
        cur = cur->next;
    }
    printf("Khong tim thay cau hoi co ID %d.\n", id);
}

void markAsDone() {
    int id;
    printf("Nhap ID cau hoi da luyen xong: ");
    scanf("%d", &id);
    NodeSLL *cur = headSLL, *prev = NULL;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next;
            else headSLL = cur->next;

            NodeDLL *doneNode = createNodeDLL(cur->data);
            if (!headDLL) {
                headDLL = tailDLL = doneNode;
            } else {
                tailDLL->next = doneNode;
                doneNode->prev = tailDLL;
                tailDLL = doneNode;
            }
            free(cur);
            printf("Da danh dau la da luyen xong.\n");
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Khong tim thay cau hoi co ID %d.\n", id);
}

void displayDoneList() {
    NodeDLL *cur = headDLL;
    if (!cur) {
        printf("Khong co cau hoi da luyen xong.\n");
        return;
    }
    while (cur) {
        printf("ID: %d | Content: %s | Topic: %s | Level: %d\n", 
               cur->data.id, cur->data.content, cur->data.topic, cur->data.level);
        cur = cur->next;
    }
}

void searchByKeyword() {
    char keyword[100];
    getchar();
    printf("Nhap tu khoa can tim: "); fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    NodeSLL *cur = headSLL;
    int found = 0;
    while (cur) {
        if (strstr(cur->data.content, keyword)) {
            printf("ID: %d | Content: %s | Topic: %s | Level: %d\n", 
                   cur->data.id, cur->data.content, cur->data.topic, cur->data.level);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) printf("Khong tim thay cau hoi nao chua tu khoa '%s'.\n", keyword);
}

void sortQuestions() {
    if (!headSLL || !headSLL->next) return;
    NodeSLL *i, *j;
    for (i = headSLL; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (strlen(i->data.content) > strlen(j->data.content)) {
                Question temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("Da sap xep danh sach cau hoi theo do dai noi dung tang dan.\n");
}

void menu() {
    int choice;
    do {
        printf("\n—————————— Interview Questions ——————————\n");
        printf("1. Them cau hoi moi\n");
        printf("2. Hien thi danh sach cau hoi dang luyen\n");
        printf("3. Cap nhat noi dung cau hoi\n");
        printf("4. Danh dau cau hoi la 'da luyen xong'\n");
        printf("5. Hien thi danh sach cau hoi da luyen xong\n");
        printf("6. Tim kiem cau hoi theo tu khoa\n");
        printf("7. Sap xep cau hoi theo do dai noi dung\n");
        printf("8. Thoat chuong trinh\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addQuestion(); break;
            case 2: displaySLL(); break;
            case 3: updateQuestion(); break;
            case 4: markAsDone(); break;
            case 5: displayDoneList(); break;
            case 6: searchByKeyword(); break;
            case 7: sortQuestions(); break;
            case 8: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
