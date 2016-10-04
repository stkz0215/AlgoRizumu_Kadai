/*
    演習1-17
    n段のピラミッドを表示する関数を作成する
*/

#include <stdio.h>

void spira(int n);

int main(void) {
    int height;

    /* 入力 */
    printf("height : ");
    scanf("%d", &height);

    /* 出力　*/
    spira(height);

    return 0;
}

void spira(int n) {
    /* n段のピラミッドを表示 */
    int i, j;

    for (i=0; i<n; i++) {
        for (j=i; j<n-1; j++) {
            putchar(' ');
        }
        for (j=0; j<2*i+1; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}