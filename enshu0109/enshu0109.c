/*
    演習1-9
    整数a,bを含め、その間の全整数の和を求めて返す
*/

#include <stdio.h>

int sumof(int a, int b);

int main(void) {
    int a = 6, b = 4;
    int tmp;

    /* 入力 */
    printf("a : ");
    scanf("%d", &a);
    printf("b : ");
    scanf("%d", &b);

    if (a > b) {    // a<=b になるようにしておく
        tmp = a;
        a = b;
        b = tmp;
    }

    /* 出力 */
    printf("sumof(%d, %d) = %d\n", a, b, sumof(a, b));

    return 0;
}

int sumof(int a, int b) {
    int res = 0;
    int i;

    for (i=a; i<=b; i++) {
        res += i;
    }

    return res;
}