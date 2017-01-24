/*
    演習2-11
    関数dayofyearを変数iとdaysを使わずに実現する
*/

#include <stdio.h>

/* 各月の日数 */
int mdays[][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int year);
int dayofyear(int y, int m, int d);

int main(void) {
    int year, month, day;
    int retry;

    do {
        /* 入力 */
        printf("年 : ");     scanf("%d", &year);
        printf("月 : ");     scanf("%d", &month);
        printf("日 : ");     scanf("%d", &day);

        /* 出力 */
        printf("年内で%d日目です。\n", dayofyear(year, month, day));

        printf("もう一度しますか (1・・・はい/0・・・いいえ) : ");
        scanf("%d", &retry);
    } while (retry == 1);

    return 0;
}

int isleap(int year) {
    /* 西暦year年はうるう年か */
    return year%4 == 0 && year%100 != 0 || year%400 == 0;
}

int dayofyear(int y, int m, int d) {
    /* 西暦y年m月d日の年内の経過日数を求める */
    while (--m > 0) {
        d += mdays[isleap(y)][m-1];
    }

    return d;
}
