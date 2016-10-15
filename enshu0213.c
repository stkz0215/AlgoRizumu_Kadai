/*
    演習2-13
    構造体YMDを使って、日付xのn日後の日付を返す関数を作成する
*/

#include <stdio.h>

typedef struct {
    int y;
    int m;
    int d;
} YMD;

/* 各月の日数 */
int mdays[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int year);
YMD after(YMD x, int n);

int main(void) {
    YMD date, date_after;
    int days;

    /* 入力 */
    printf("年 : ");     scanf("%d", &date.y);
    printf("月 : ");     scanf("%d", &date.m);
    printf("日 : ");     scanf("%d", &date.d);
    printf("何日後 : ");   scanf("%d", &days);

    /* 関数呼び出し */
    date_after = after(date, days);

    /* 出力 */
    printf("西暦%d年%d月%d日の%d日後は\n", date.y, date.m, date.d, days);
    printf("西暦%d年%d月%d日です。\n", date_after.y, date_after.m, date_after.d);

    return 0;
}

int isleap(int year) {
    /* 西暦year年はうるう年か */
    return year%4 == 0 && year%100 != 0 || year%400 == 0;
}

YMD after(YMD x, int n) {
    /* 日付xのn日後の日付を返す */
    YMD res;

    res.y = x.y;
    res.m = x.m;
    res.d = x.d+n;

    while (res.d > mdays[isleap(res.y)][res.m]) {
        res.d -= mdays[isleap(res.y)][res.m];

        if(res.m >= 12) {
            ++res.y;
            res.m = 1;
        } else {
            ++res.m;
        }
    }

    return res;
}
