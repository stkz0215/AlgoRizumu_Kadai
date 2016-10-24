/*
    ���K:InsertAfter�̎����i�|�C���^�Łj
    �w��m�[�h�̎��Ƀm�[�h��}������֐����쐬����
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ����f�[�^ */
typedef struct {
    int no;         // �ԍ�
    char name[20];  // ����
} Member;

/* ���`���X�g�p�m�[�h */
typedef struct __node {
    Member          data;   // �f�[�^
    struct __node  *next;   // �㑱�|�C���^
} Node;

/* ���`���X�g */
typedef struct {
    Node *head;     // �擪�m�[�h�ւ̃|�C���^
    Node *crnt;     // ���ڃm�[�h�ւ̃|�C���^
} List;

/* ���`���X�g������ */
void InitList(List *list) {
    list->head = NULL;
    list->crnt = NULL;
}

/* 1�̃m�[�h�𓮓I�ɐ��� */
static Node *AllocNode(void) {
    return calloc(1, sizeof(Node));
}

/* �S�m�[�h�����X�g���ɕ\�� */
void PrintList(List *list) {
    int cont = 0;
    list->crnt = list->head;
    puts("---------------------------");
    puts("        No.| Name");
    puts("---------------------------");
    while (list->crnt != NULL) {
        printf("[%2d] %5d | %s\n", cont, list->crnt->data.no, list->crnt->data.name);
        list->crnt = list->crnt->next;
        cont++;
    }
    puts("---------------------------");
}

/*�@���X�g�̐擪�Ƀm�[�h��}���@*/
void InsertFront(List *list, const Member *x) {
    Node *ptr = list->head;
    list->head = list->crnt = AllocNode();
    list->crnt->data = *x;
    list->crnt->next = ptr;
}

/* ---- �ۑ�̊֐� ---- */
/* �w��m�[�h�̎��Ƀm�[�h��}�� */
void InsertAfter(List *list, Node *p, const Member *x) {
    list->crnt = AllocNode();
    list->crnt->data = *x;
    list->crnt->next = p->next;
    p->next = list->crnt;
}
/* ---- �ۑ肱���܂� ---- */


/* �m�F�p�T���v���v���O���� */
int main(void) {
    List *list;   // �T���v���p���X�g
    char name_init[][20] = {"Sato", "Suzuki", "Takahashi", "Tanaka", "Ito"};
    int flag_loop;
    int i;

    puts("-pointer��-");

    list = calloc(1, sizeof(List));
    InitList(list);     // ���`���X�g������

    /* �������X�g�쐬 */
    for (i=0; i<5; ++i) {
        Member tmp_member;
        tmp_member.no = i+1;
        strcpy(tmp_member.name, name_init[i]);

        if (i == 0) InsertFront(list, &tmp_member);
        else        InsertAfter(list, list->crnt, &tmp_member);
        
        list->crnt = list->head;
        while(list->crnt->next != NULL)  list->crnt = list->crnt->next;
    }    

    /* �m�[�h�}�� */
    flag_loop = 1;
    while (flag_loop == 1) {
        int n, num;
        char name[20];
        Node *p;
        Member member;

        PrintList(list);
        printf("�����Ԃ̌��ɑ}�����܂��� : ");   scanf("%d", &num);
        p = list->head;
        for (i=0; i<num && p != NULL; i++) {
            p = p->next;
        }

        if(p == NULL || num < 0) {
            puts("ERROR : ��������͂ł��B");
        } else {
            printf("No   : ");  scanf("%d", &member.no);
            printf("Name : ");  scanf("%s", member.name);
            InsertAfter(list, p, &member);
            puts("-----");
            puts("�}�����܂��� :");
            PrintList(list);
        }
        printf("�}���𑱂��܂���(Yes:1/No:1�ȊO) : ");
        scanf("%d", &flag_loop);
        puts("-----");
    }   
    
    return 0;
}
