/*
    演習:InsertAfterの実装（ポインタ版）
    指定ノードの次にノードを挿入する関数を作成する
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 会員データ */
typedef struct {
    int no;         // 番号
    char name[20];  // 氏名
} Member;

/* 線形リスト用ノード */
typedef struct __node {
    Member          data;   // データ
    struct __node  *next;   // 後続ポインタ
} Node;

/* 線形リスト */
typedef struct {
    Node *head;     // 先頭ノードへのポインタ
    Node *crnt;     // 着目ノードへのポインタ
} List;

/* 線形リスト初期化 */
void InitList(List *list) {
    list->head = NULL;
    list->crnt = NULL;
}

/* 1つのノードを動的に生成 */
static Node *AllocNode(void) {
    return calloc(1, sizeof(Node));
}

/* 全ノードをリスト順に表示 */
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

/*　リストの先頭にノードを挿入　*/
void InsertFront(List *list, const Member *x) {
    Node *ptr = list->head;
    list->head = list->crnt = AllocNode();
    list->crnt->data = *x;
    list->crnt->next = ptr;
}

/* ---- 課題の関数 ---- */
/* 指定ノードの次にノードを挿入 */
void InsertAfter(List *list, Node *p, const Member *x) {
    list->crnt = AllocNode();
    list->crnt->data = *x;
    list->crnt->next = p->next;
    p->next = list->crnt;
}
/* ---- 課題ここまで ---- */


/* 確認用サンプルプログラム */
int main(void) {
    List *list;   // サンプル用リスト
    char name_init[][20] = {"Sato", "Suzuki", "Takahashi", "Tanaka", "Ito"};
    int flag_loop;
    int i;

    puts("-pointer版-");

    list = calloc(1, sizeof(List));
    InitList(list);     // 線形リスト初期化

    /* 初期リスト作成 */
    for (i=0; i<5; ++i) {
        Member tmp_member;
        tmp_member.no = i+1;
        strcpy(tmp_member.name, name_init[i]);

        if (i == 0) InsertFront(list, &tmp_member);
        else        InsertAfter(list, list->crnt, &tmp_member);
        
        list->crnt = list->head;
        while(list->crnt->next != NULL)  list->crnt = list->crnt->next;
    }    

    /* ノード挿入 */
    flag_loop = 1;
    while (flag_loop == 1) {
        int n, num;
        char name[20];
        Node *p;
        Member member;

        PrintList(list);
        printf("↑何番の後ろに挿入しますか : ");   scanf("%d", &num);
        p = list->head;
        for (i=0; i<num && p != NULL; i++) {
            p = p->next;
        }

        if(p == NULL || num < 0) {
            puts("ERROR : 誤った入力です。");
        } else {
            printf("No   : ");  scanf("%d", &member.no);
            printf("Name : ");  scanf("%s", member.name);
            InsertAfter(list, p, &member);
            puts("-----");
            puts("挿入しました :");
            PrintList(list);
        }
        printf("挿入を続けますか(Yes:1/No:1以外) : ");
        scanf("%d", &flag_loop);
        puts("-----");
    }   
    
    return 0;
}
