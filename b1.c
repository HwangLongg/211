#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    int credit;
} Course;

// Danh sách liên kết đơn cho khóa học đang học
typedef struct CourseNode {
    Course data;
    struct CourseNode* next;
} CourseNode;

// Danh sách liên kết đôi cho khóa học đã hoàn thành
typedef struct CompletedNode {
    Course data;
    struct CompletedNode* prev;
    struct CompletedNode* next;
} CompletedNode;

CourseNode* head = NULL;              // Danh sách đang học
CompletedNode* completedHead = NULL; // Danh sách đã hoàn thành

// Thêm khóa học mới
void themKhoaHoc() {
    CourseNode* newNode = (CourseNode*)malloc(sizeof(CourseNode));
    printf("Nhap ID: ");
    scanf("%d", &newNode->data.id);
    getchar(); // loại bỏ '\n' sau scanf
    printf("Nhap ten khoa hoc: ");
    fgets(newNode->data.title, 100, stdin);
    newNode->data.title[strcspn(newNode->data.title, "\n")] = '\0';
    printf("Nhap so tin chi: ");
    scanf("%d", &newNode->data.credit);
    newNode->next = head;
    head = newNode;
    printf("Da them khoa hoc!\n");
}

// Hiển thị danh sách đang học
void hienThiDanhSach() {
    CourseNode* temp = head;
    if (!temp) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("\nDanh sach khoa hoc dang hoc:\n");
    while (temp) {
        printf("ID: %d | Ten: %s | Tin chi: %d\n", temp->data.id, temp->data.title, temp->data.credit);
        temp = temp->next;
    }
}

// Xóa khóa học theo ID
void xoaKhoaHoc() {
    int id;
    printf("Nhap ID muon xoa: ");
    scanf("%d", &id);
    CourseNode *temp = head, *prev = NULL;
    while (temp) {
        if (temp->data.id == id) {
            if (!prev) head = temp->next;
            else prev->next = temp->next;
            free(temp);
            printf("Da xoa!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay khoa hoc!\n");
}

// Cập nhật thông tin khóa học
void capNhatKhoaHoc() {
    int id;
    printf("Nhap ID muon cap nhat: ");
    scanf("%d", &id);
    CourseNode* temp = head;
    while (temp) {
        if (temp->data.id == id) {
            getchar();
            printf("Nhap ten moi: ");
            fgets(temp->data.title, 100, stdin);
            temp->data.title[strcspn(temp->data.title, "\n")] = '\0';
            printf("Nhap tin chi moi: ");
            scanf("%d", &temp->data.credit);
            printf("Da cap nhat!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Khong tim thay khoa hoc!\n");
}

// Đánh dấu khóa học đã hoàn thành
void hoanThanhKhoaHoc() {
    int id;
    printf("Nhap ID khoa hoc hoan thanh: ");
    scanf("%d", &id);
    CourseNode *temp = head, *prev = NULL;

    while (temp) {
        if (temp->data.id == id) {
            // Xóa khỏi danh sách đang học
            if (!prev) head = temp->next;
            else prev->next = temp->next;

            // Thêm vào danh sách hoàn thành
            CompletedNode* newNode = (CompletedNode*)malloc(sizeof(CompletedNode));
            newNode->data = temp->data;
            newNode->prev = NULL;
            newNode->next = completedHead;
            if (completedHead) completedHead->prev = newNode;
            completedHead = newNode;

            free(temp);
            printf("Da chuyen sang da hoan thanh!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay khoa hoc!\n");
}

// Hiển thị danh sách khóa học đã hoàn thành
void hienThiDaHoanThanh() {
    CompletedNode* temp = completedHead;
    if (!temp) {
        printf("Chua co khoa hoc hoan thanh nao.\n");
        return;
    }
    printf("\nDanh sach khoa hoc da hoan thanh:\n");
    while (temp) {
        printf("ID: %d | Ten: %s | Tin chi: %d\n", temp->data.id, temp->data.title, temp->data.credit);
        temp = temp->next;
    }
}

// Giải phóng bộ nhớ
void giaiPhong() {
    CourseNode* cur = head;
    while (cur) {
        CourseNode* next = cur->next;
        free(cur);
        cur = next;
    }

    CompletedNode* c = completedHead;
    while (c) {
        CompletedNode* next = c->next;
        free(c);
        c = next;
    }
}

// Menu chính
void menu() {
    int chon;
    do {
        printf("\n----- MENU QUAN LY KHOA HOC -----\n");
        printf("1. Them khoa hoc\n");
        printf("2. Hien thi danh sach dang hoc\n");
        printf("3. Xoa khoa hoc\n");
        printf("4. Cap nhat khoa hoc\n");
        printf("5. Danh dau da hoan thanh\n");
        printf("6. Hien thi khoa hoc da hoan thanh\n");
        printf("7. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1: themKhoaHoc(); break;
            case 2: hienThiDanhSach(); break;
            case 3: xoaKhoaHoc(); break;
            case 4: capNhatKhoaHoc(); break;
            case 5: hoanThanhKhoaHoc(); break;
            case 6: hienThiDaHoanThanh(); break;
            case 7: giaiPhong(); printf("Da thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (chon != 7);
}

// Hàm main
int main() {
    menu();
    return 0;
}
