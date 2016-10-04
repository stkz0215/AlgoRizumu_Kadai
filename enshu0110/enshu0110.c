/*
    演習1-10
    二つの変数a,bに整数値を読み込んでb-aの値を表示する。
    ただし、変数bに読み込んだ値がa以下なら変数bの値を再入力させる。
*/

#include <stdio.h>

int main(void) {
    int a, b;

    /* 入力 */
    printf("aの値 : ");
    scanf("%d", &a);

    for (;;) {  // aより大きいbが入力されるまでループ
        printf("bの値 : ");
        scanf("%d", &b);
        if (b <= a)
            printf("aより大きな値を入力せよ!\n");
        else
            break;
    }

    /* 出力 */
    printf("b-aは%dです。\n", b-a);

    return 0;
}