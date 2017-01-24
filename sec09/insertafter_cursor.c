/*
    演習:InsertAfterの実装（カーソル版）
    指定ノードの次にノードを挿入する関数を作成する
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Null -1
#define SIZE 100

/* カーソル型 */
typedef int Index;

/* 会員データ */
typedef struct {
    int no;         // 番号
    char name[20];  // 氏名
} Member;

/* 線形リスト用ノード */
typedef struct {
    Member data;    // データ
    Index next;     // 後続ノード
    Index Dnext;    // フリーリストの後続ノード
} Node;

/* 線形リスト */
typedef struct {
    Node *n;        // リスト本体（配列）
    Index head;     // 先頭ノード
    Index max;      // 利用中の末尾レコード
    Index deleted;  // フリーリストの先頭ノード
    Index crnt;     // 着目ノード
} List;

/* 線形リスト初期化 */
void InitList(List *list, int size) {
    list->n = calloc(size, sizeof(Node));
    list->head = Null;
    list->max = Null;
    list->deleted = Null;
    list->crnt = Null;
}

/* 挿入するレコードのインデックスを求める */
static Index GetIndex(List *list) {
    if(list->deleted == Null) {
        return ++(list->max);
    } else {
        Index rec = list->deleted;
        list->deleted = list->n[rec].Dnext;
        return rec;
    }
}

/* 全ノードをリスト順に表示 */
void PrintList(List *list) {
    int cont = 0;
    list->crnt = list->head;
    puts("---------------------------");
    puts("        No.| Name");
    puts("---------------------------");
    while (list->crnt != Null) {
        printf("[%2d] %5d | %s\n", cont, list->n[list->crnt].data.no, list->n[list->crnt].data.name);
        list->crnt = list->n[list->crnt].next;
        cont++;
    }
    puts("---------------------------");
}

/*　リストの先頭にノードを挿入　*/
void InsertFront(List *list, const Member *x) {
    Index ptr = list->head;
    list->head = list->crnt = GetIndex(list);
    list->n[list->crnt].data = *x;
    list->n[list->crnt].next = ptr;
}

/* ---- 課題の関数 ---- */
/* 指定ノードの次にノードを挿入 */
void InsertAfter(List *list, Index idx, const Member *x) {
    list->crnt = GetIndex(list);
    list->n[list->crnt].data = *x;
    list->n[list->crnt].next = list->n[idx].next;
    list->n[idx].next = list->crnt;
}
/* ---- 課題ここまで ---- */


/* 確認用サンプルプログラム */
int main(void) {
    List *list;   // サンプル用リスト
    char name_init[][20] = {"Sato", "Suzuki", "Takahashi", "Tanaka", "Ito"};
    int flag_loop;
    int i;

    puts("-cursor版-");

    list = calloc(1, sizeof(list));
    InitList(list, SIZE);     // 線形リスト初期化

    /* 初期リスト作成 */
    for (i=0; i<5; ++i) {
        Member tmp_member;
        tmp_member.no = i+1;
        strcpy(tmp_member.name, name_init[i]);

        if (i == 0) InsertFront(list, &tmp_member);
        else        InsertAfter(list, list->crnt, &tmp_member);
        
        list->crnt = list->head;
        while(list->n[list->crnt].next != Null)  list->crnt = list->n[list->crnt].next;
    }    

    /* ノード挿入 */
    flag_loop = 1;
    while (flag_loop == 1) {
        int n, num;
        char name[20];
        Index idx;
        Member member;

        PrintList(list);
        printf("↑何番の後ろに挿入しますか : ");   scanf("%d", &num);
        idx = list->head;
        for (i=0; i<num && idx != Null; i++) {
            idx = list->n[idx].next;
        }

        if(idx == Null || num < 0) {
            puts("ERROR : 誤った入力です。");
        } else {
            printf("No   : ");  scanf("%d", &member.no);
            printf("Name : ");  scanf("%s", member.name);
            InsertAfter(list, idx, &member);
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
