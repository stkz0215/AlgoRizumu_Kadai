/*
	1からnまでの合計を求める関数int siguma(int n) を
	for, while, do-while, 再帰の4バージョンで作成
*/

#include <stdio.h>

/* 関数プロトタイプ */
int siguma_for(int n);
int siguma_while(int n);
int siguma_do(int n);
int siguma_rec(int n);

int main(void) {
	int n;

	/* 入力 */
	puts("1から入力された数までの合計を計算します。");
	do {
		printf("正の整数を入力してください:");
		scanf("%d", &n);
	} while (n <= 0);

	/* 出力 */
	printf("siguma_for(%d)   = %d\n", n, siguma_for(n));
	printf("siguma_while(%d) = %d\n", n, siguma_for(n));
	printf("siguma_do(%d)    = %d\n", n, siguma_for(n));
	printf("siguma_rec(%d)   = %d\n", n, siguma_for(n));

	return 0;
}

/* ---1からnまでの合計を求める関数--- */
/* for版 */
int siguma_for(int n) {
	int res = 0;
	int i;

	for (i=1; i<=n; i++) {
		res += i;
	}

	return res;
}

/* while版 */
int siguma_while(int n) {
	int res = 0;
	int i = 0;

	while (i < n) {
		res += ++i;
	}

	return res;
}

/* do-while版 */
int siguma_do(int n) {
	int res = 0;
	int i = 0;

	do {
		res += ++i;
	} while(i < n);
}

/* 再帰版 */
int siguma_rec(int n) {
	if (n == 1) {
		return 1;
	} else {
		return siguma_rec(n-1) + n;
	}
}
