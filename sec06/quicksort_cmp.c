#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum PT {HEAD, CENTER, END, MEDIAN} PivotType;	// ピボットの取り方（先頭・中央・末尾・左3つの値の中央値）

void quicksort(int *data, int left, int right, PivotType pt);
int compare(int a, int b);
void swap(int *d, int a, int b);
void initRandData(int *d, int n);
void initAscendingData(int *d, int n);
void initDescendingData(int *d, int n);
void printdata(int *d, int n);

unsigned long counterSwap;
unsigned long counterComp;

int main(void)
{  
	int *data;		// 配列データ用のポインタ
	int com;		// データタイプ 1:ランダム 2:昇順 3:降順
	int datasize[3] = {1000, 5000, 10000};		// データのサイズ
	int i, j;
	char outputstr[][11] = {"Head", "Center", "End", "Median", "Random", "Ascending", "Descending"};
	void (* initData[3])(int *d, int x) = {initRandData,
	                                       initAscendingData,
	                                       initDescendingData };
	FILE *fp;

	/* 出力ファイルをオープン */
	if ((fp = fopen("output.txt", "w")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	
	for (i=0; i<4; i++) {
		fputs("------------------------------\n", fp);
		fprintf(fp, "Pivot : %s\n", outputstr[i]);
		for (com=1; com<=3; com++) {
			fprintf(fp, "--Array : %s\n", outputstr[com+3]);
			for (int j=0; j<3; j++) {
				fprintf(fp, "    Size : %d\n", datasize[j]);
				/* カウンタリセット */
				counterSwap = 0;
				counterComp = 0;

				/* データ列取得 */
				data = (int*) malloc(sizeof(int) *datasize[j]);
				if(com==0) {
					for (i=0; i<datasize[j]; i++) {
						scanf("%d", &data[i]);
					}
				} else {
					initData[com-1](data, datasize[j]);
				}

				/* クイックソート実行 */
				quicksort(data, 0, datasize[j]-1, i);

				/* 結果出力 */
				fprintf(fp, "      compare : %d\n", counterComp);
				fprintf(fp, "      swap    : %d\n", counterSwap);

				free(data);		// メモリ開放
			}
		}
	}

	fclose(fp);	// 出力ファイルをクローズ

	return 0;
}

/* クイックソート */
void quicksort(int *data, int left, int right, PivotType pt)
{
	int pivot;			// ピボット
	int small, large;	//　ピボットより大きい/小さいもの
	int center = (left+right) / 2;		// 配列の中央の位置

	if(left < right) {	// 要素が2つ以上のとき
		small = left;
		large = right;

		/* ピボットの値決め */
		switch(pt) {
			case HEAD:		// 先頭
				pivot = data[left]; 
				break;
			case CENTER:	// 中央
				pivot = data[center]; 
				break;
			case END:		// 末尾
				pivot = data[right]; 
				break;
			case MEDIAN:	// 先頭・中央・末尾の3値の中央値
				// 3値の比較から中央値を決定
				if(data[left] < data[right]) {
					if(data[center] < data[left]) {
						pivot = data[left];
					} else if(data[center] < data[right]) {
						pivot = data[center];
					} else {
						pivot = data[right];
					}
				} else {
					if(data[center] < data[right]) {
						pivot = data[right];
					} else if(data[center] < data[left]) {
						pivot = data[center];
					} else {
						pivot = data[left];
					}
				}
		}

		while(small<=large){	// 調べる場所が交差するまで
			while(compare(data[small], pivot)) small++;	// ピボットより大きい値が出てくるまで右へずらす
			while(compare(pivot, data[large])) large--;	// ピボットより小さい値が出てくるまで左へずらす
			if(small<=large){	// 調べる場所が交差していないとき
				swap(data, small++, large--);			// それぞれ止まったところで入れ替え
			}
		}
		
		if (left < large)  quicksort(data, left, large, pt);	// ピボットより大きい値が2つ以上あるとき、それらで再度ソート
		if (small < right) quicksort(data, small, right, pt);	// ピボットより小さい値が2つ以上あるとき、それらで再度ソート
	}
}

/* 比較関数 */
int compare(int a, int b)
{
	counterComp++;	// 比較回数を1増やす
	return (a<b);	// a<bのとき1を返す
}

/* 交換関数 */
void swap(int *d, int a, int b)
{
	int tmp;

	counterSwap++;	// 交換回数を1増やす
	tmp = d[a];		// 配列dのa番目の要素とb番目の要素を交換
	d[a] = d[b];
	d[b] = tmp;
}

/* 要素数nのランダムな配列を生成 */
void initRandData(int *d, int n)
{
	int i, s;
	srand(time(NULL));
	s=n*10;
	for(i=0; i<n; i++) d[i]=rand()%s;
}

/* 要素数nの昇順な配列を生成 */
void initAscendingData(int *d, int n)
{
	int i;
	for(i=0; i<n; i++)  d[i]=i;
}

/* 要素数nの降順な配列を生成 */
void initDescendingData(int *d, int n)
{
	int i;
	for(i=0; i<n; i++)  d[i]=n-i-1;
}
