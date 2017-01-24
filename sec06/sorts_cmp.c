#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum ST {BUBBLE, SELECTION, INSERTION, SHELL, QUICK, MERGE, HEAP} SortType;

void sort(int *data, int n, SortType st);
void bubblesort(int *data, int n);
void selectionsort(int *data, int n);
void insertionsort(int *data, int n);
void shellsort(int *data, int n);
void quicksort(int *data, int left, int right);
void mergesort(int *data, int left, int right);
void heapsort(int *data, int n);
int compare(int a, int b);
void swap(int *d, int a, int b);
void merge(int *data,int left,int mid, int right);
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
	int datasize[6] = {1000, 5000, 10000, 30000, 50000, 100000}; // データのサイズ
	int i, j;
	char outputstr[][11] = {"Bubble", "Selection", "Insertion", "Shell", "Quick", "Merge", "Heap", "Random", "Ascending", "Descending"};
	void (* initData[3])(int *d, int x) = {initRandData,
	                                       initAscendingData,
	                                       initDescendingData };
	FILE *fp;

	/* 出力ファイルをオープン */
	if ((fp = fopen("output.txt", "w")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	
	for (i=0; i<7; i++) {
		fputs("------------------------------\n", fp);
		fprintf(fp, "Sort : %s\n", outputstr[i]);
		puts("------------------------------");
		printf("Sort : %s\n", outputstr[i]);
		for (com=1; com<=3; com++) {
			fprintf(fp, "--Array : %s\n", outputstr[com+6]);
			printf("--Array : %s\n", outputstr[com+6]);
			for (int j=0; j<6; j++) {
				fprintf(fp, "    Size : %d\n", datasize[j]);
				printf("    Size : %d\n", datasize[j]);
				/* ランダムの場合 */
				if(com == 1) {
					int k;
					unsigned long long aveSwap = 0;
					unsigned long long aveComp = 0;
					for (k=0; k<3; k++) {
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

						/* ソート実行 */
						sort(data, datasize[j], i);

						aveSwap += counterSwap;
						aveComp += counterComp;

						free(data);		// メモリ開放
					}
					
					/* 結果出力 */
					fprintf(fp, "      compare : %d\n", aveComp / 3);
					fprintf(fp, "      swap    : %d\n", aveSwap / 3);
				}
				/* ランダム以外 */
				else {
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

					/* ソート実行 */
					sort(data, datasize[j], i);

					/* 結果出力 */
					fprintf(fp, "      compare : %d\n", counterComp);
					fprintf(fp, "      swap    : %d\n", counterSwap);

					free(data);		// メモリ開放
				}
			}
		}
	}

	fclose(fp);	// 出力ファイルをクローズ

	return 0;
}

/* 各種ソート呼び出し関数 */
void sort(int *data, int n, SortType st) {
	switch(st) {
		case BUBBLE:
			//puts("bubble");
			bubblesort(data, n);
			break;
		case SELECTION:
			//puts("selection");
			selectionsort(data, n);
			break;
		case INSERTION:
			//puts("insertion");
			insertionsort(data, n);
			break;
		case SHELL:
			//puts("shell");
			shellsort(data, n);
			break;
		case QUICK:
			//puts("quick");
			quicksort(data, 0, n-1);
			break;
		case MERGE:
			//puts("merge");
			mergesort(data, 0, n-1);
			break;
		case HEAP:
			//puts("heap");
			heapsort(data, n);
	}
}

/* 単純交換ソート */
void bubblesort(int *data, int n) {
	int i, j;
	
	for (i=0; i<n-1; i++) {
		for (j=n-1; j>i; j--) {
			if(compare(data[j], data[j-1])) {
				swap(data, j, j-1);
			}
		}
	}
}

/* 単純選択ソート */
void selectionsort(int *data, int n) {
	int i, j;

	for (i=0; i<n-1; i++) {
		int min = i;
		for (j=i+1; j<n; j++) {
			if(compare(data[j], data[min])) {
				min = j;
			}
		}
		swap(data, i, min);
	}
}

/* 単純挿入ソート */
void insertionsort(int *data, int n) {
	int i, j;

	for (i=1; i<n; i++) {
		for (j=i; j>0; j--) {
			if(compare(data[j-1], data[j]) || data[j-1] == data[j]) {
				break;
			}
			swap(data, j-1, j);
		}
	}
}

/* シェルソート */
void shellsort(int *data, int n) {
	int gap;
	int temp;
	int i, j;

    for (gap = n / 2; gap > 0; gap /= 2) {
    	for (i = gap; i < n; i ++) {
    		for (j = i - gap; j >= 0; j -= gap) { /* このループで */
        	    if (compare(data[j], data[j + gap]) || data[j] == data[j+gap]) /* j 番目とj + gap 番目と比較 */
        	        break;       /* ここにbreak;を挿入。H.O.さんご指摘ありがとうございました。 */
        	    else {
        	        swap(data, j, j+gap);
        	    }
        	}
    	}
    }
        
}

/* クイックソート */
void quicksort(int *data, int left, int right)
{
	int pivot;			// ピボット
	int small, large;	//　ピボットより大きい/小さいもの
	int center = (left+right) / 2;		// 配列の中央の位置

	if(left < right) {	// 要素が2つ以上のとき
		small = left;
		large = right;

		/* ピボットの値決め-3値の中央値 */
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

		while(small<=large){	// 調べる場所が交差するまで
			while(compare(data[small], pivot)) small++;	// ピボットより大きい値が出てくるまで右へずらす
			while(compare(pivot, data[large])) large--;	// ピボットより小さい値が出てくるまで左へずらす
			if(small<=large){	// 調べる場所が交差していないとき
				swap(data, small++, large--);			// それぞれ止まったところで入れ替え
			}
		}
		
		if (left < large)  quicksort(data, left, large);	// ピボットより大きい値が2つ以上あるとき、それらで再度ソート
		if (small < right) quicksort(data, small, right);	// ピボットより小さい値が2つ以上あるとき、それらで再度ソート
	}
}

/* マージソート */
void mergesort(int *data, int left, int right)
{
	int mid;

	if(left<right){
		mid = (right+left)/2;
		mergesort(data, left, mid);
		mergesort(data, mid+1, right);
		merge(data, left, mid+1, right);
	}
}

/* ヒープソート */
void heapsort(int *data, int n)
{
	int parent, childe;
	int i;

	for(i=(n-1)/2; i>=0; i--){
		parent = i;
		childe = 2 * parent + 1;
		while(childe < n){
			if(childe < n-1 && compare(data[childe], data[childe + 1]))
				childe = childe +1;
			if(compare(data[parent], data[childe])) {
				swap(data, parent, childe);
				parent = childe; childe = 2 * parent + 1;
			} else
				break;
		}
	}

	for(i=n-1; i>0; i--) {
		swap(data, 0, i);
		parent = 0;
		childe = 1;
		while(childe < i) {
			if(childe  < i-1 && compare(data[childe], data[childe + 1]))
				childe = childe +1;
			if( compare(data[parent], data[childe])) {
				swap(data, parent, childe);
				parent = childe;
				childe = 2 * parent + 1;
			} else {
				break;
			}
		}
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

/* マージ */
void merge(int *data,int left,int mid, int right)
{
	int *tmp;
	int i, j, k;

	tmp = (int*) malloc(sizeof(int)*(right-left+1));

	i = left;
	j = mid;
	k = 0;

	while ((i<mid) && (j<=right)) {
		if (compare(data[i], data[j])) tmp[k++] = data[i++];
		else                           tmp[k++] = data[j++];
	}

	while (i<mid)    tmp[k++] = data[i++];
	while (j<=right) tmp[k++] = data[j++];

	for(i=left; i<=right; i++) {
		data[i] = tmp[i-left];
	}

	free(tmp);
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
