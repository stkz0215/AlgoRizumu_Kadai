/*
	演習3-8
	bsearch関数と同じ形式で呼び出せる関数binsearchを作成する
	探索には2分探索を使用する
*/

#include <stdio.h>
#include <stdlib.h>

/* 整数を比較する関数 */
int int_cmp(const void *a, const void *b) {
	if(*(int *)a < *(int *)b)
		return -1;
	else if(*(int *)a > *(int *)b)
		return 1;
	else
		return 0;
}

/* ---- 課題の関数 ---- */
/* baseが指すオブジェクトの配列からkeyが指すオブジェクトに一致する要素を探索　*/
void *binserch(const void *key, const void *base, size_t nmemb,
	size_t size, int (*compar)(const void *, const void *)) {

	int pl = 0;
	int pr = nmemb-1;
	int pc;
	int cmp;

	/* 2分探索 */
	do {
		pc = (pl + pr) / 2;
		cmp = compar((const void *)((char *)base+size*pc), key);
		// baseをchar（1バイト）にキャストしたアドレスの値にsize*pcを足すとpc番目の要素を見れる
		
		if(cmp == 0)  {
			return (void *)((char *)base+size*pc);
		}
		else if(cmp < 0)
			pl = pc+1;
		else
			pr = pc-1;
	} while(pl <= pr);

	return NULL;
}
/* ---- 関数ここまで ---- */

int main(void) {
	int i, nx, ky;
	int *x;		// 配列の先頭要素へのポインタ
	int *p;		// 探索された要素へのポインタ

	puts("binsearch関数による探索");
	printf("要素数 : ");
	scanf("%d", &nx);
	x = calloc(nx, sizeof(int));

	printf("昇順に入力してください。\n");
	printf("x[0] : ");
	scanf("%d", &x[0]);

	for (i=1; i<nx; i++) {
		do {
			printf("x[%d] : ", i);
			scanf("%d", &x[i]);
		} while (x[i] < x[i-1]);
	}

	printf("探す値 : ");
	scanf("%d", &ky);
	
	p = binserch(&ky,			// 探索値へのポインタ
				 x,				// 配列
				 nx,			// 要素数
				 sizeof(int),	// 要素の大きさ
				 (int (*)(const void *, const void *))int_cmp	// 比較関数
				);

	if(p == NULL)
		puts("探索に失敗しました。");
	else
		printf("%dはx[%d]にあります。\n", ky, (int)(p-x));

	free(x);

	return 0;
}