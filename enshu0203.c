/*
    演習2-3
    要素数がnである配列aの全要素の平均を実数値で求める関数を作成する
*/

#include <stdio.h>
#include <stdlib.h>

double aveof(const int a[], int n);

int main(void) {
    int i; 
    int *height;
    int number;

    /* 入力 */
    printf("人数 : ");
    scanf("%d", &number);

    height = calloc(number, sizeof(int));

    printf("%d人の身長を入力してください。\n", number);
    for (i=0; i<number; i++) {
        printf("height[%d] : ", i);
        scanf("%d", &height[i]);
    }

    /* 出力 */
    printf("平均値は%fです。\n", aveof(height, number));
    free(height);

    return 0;
} 

double aveof(const int a[], int n) {
    /* a[]に格納された値の平均値を求める */
    double sum = 0;
    int i;

    for (i=0; i<n; i++) {
        sum += a[i];
    }

    return sum / n;
}
