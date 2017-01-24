/*
	演習:スタックの実装
	ポインタ版リスト構造によるスタックを実装する。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	・スタックは動的に領域を確保してメモリの許す限り
	 いくつでもデータが入るようになっている
*/

/* ノード */
typedef struct node
{
	char 		 data;
	struct node *next;
} Node;

/* リスト */
typedef struct {
	Node *head;
	Node *crnt;
} List;

/* スタック */
typedef struct {
	int  max;
	int  num;
	List stk;
} Stack;

/* スタックの初期化 */
void Initialize(Stack *s) {
	s->max = 0;		// 今回は使用しない
	s->num = 0;
	s->stk.head = NULL;
	s->stk.crnt = NULL;
}

/* スタックにデータをプッシュ */
int Push(Stack *s, char data) {
	s->stk.crnt = s->stk.head;

	if((s->stk.head = calloc(1, sizeof(Node))) == NULL)
		return -1;
	s->stk.head->data = data;
	s->stk.head->next = s->stk.crnt;
	s->num++;

	return 0;
}

/* スタックからデータをポップ */
int Pop(Stack *s, char *x) {
	if(s->num <= 0)
		return -1;
	s->stk.crnt = s->stk.head->next;
	*x = s->stk.head->data;
	free(s->stk.head);
	s->stk.head = s->stk.crnt;
	s->num--;

	return 0;
}

/* スタックの一番上の値をのぞく */
int Peek(const Stack *s, char *x) {
	if(s->num <= 0)
		return -1;
	*x = s->stk.head->data;

	return 0;
}

/* スタックを空にする */
void Clear(Stack *s) {
	while (s->stk.head != NULL) {
		s->stk.crnt = s->stk.head->next;
		free(s->stk.head);
		s->stk.head = s->stk.crnt;
	}
	Initialize(s);
}

/* スタックに積まれているデータ数 */
int Size(const Stack *s) {
	return s->num;
}

/* スタックは空か */
int IsEmpty(const Stack *s) {
	return (s->num <= 0);
}

/* スタックからの探索 */
int Search(Stack *s, char *x) {
	int i = 1;

	s->stk.crnt = s->stk.head;
	while(s->stk.crnt != NULL) {
		if(s->stk.crnt->data == *x)
			return i;
		s->stk.crnt = s->stk.crnt->next;
		i++;
	}

	return -1;
}

/* 全データの表示 */
void Print(Stack *s) {
	if(IsEmpty(s)) {
		puts("No data.");
		return;
	}

	s->stk.crnt = s->stk.head;
	puts("[Top]");
	while(s->stk.crnt != NULL) {
		printf("%d\n", s->stk.crnt->data);
		s->stk.crnt = s->stk.crnt->next;
	}
	puts("[Bottom]");
}

/* スタックの後始末 */
void Terminate(Stack *s) {
	while (s->stk.head != NULL) {
		s->stk.crnt = s->stk.head->next;
		free(s->stk.head);
		s->stk.head = s->stk.crnt;
	}
}

/* サンプル */
int main(void) {
	Stack s;
	Initialize(&s);

	while (1) {
		int  menu;
		char x;

		printf("Number of data : %d\n", Size(&s));
		printf("/ 1:Push / 2:Pop / 3:Peek / 4:Print / 5:Clear / 6:Search / 0:Exit / : ");
		scanf("%d", &menu);

		if(menu == 0) break;

		switch (menu) {
		 case 1:	// プッシュ
			printf("Data : ");
			scanf("%d", &x);
			if(Push(&s, x) == -1)
				puts("[ERROR]Failed to push the data.");
			else
				puts("Pushed successfully.");
			break;
		 case 2:	// ポップ
			if(Pop(&s, &x) == -1)
				puts("[ERROR]Failed to pop the data.");
			else
				printf("Poped successfully : %d.\n", x);
			break;
		 case 3:	// ピーク
			if(Peek(&s, &x) == -1)
				puts("[ERROR]Failed to peek the data.");
			else
				printf("Peeked successfully : %d.\n", x);
			break;
		 case 4:	// 表示
			Print(&s);
			break;
		 case 5:	// クリア
			Clear(&s);
			puts("Cleared.");
			break;
		 case 6:	// サーチ
			printf("Data : ");
			scanf("%d", &x);
			printf("\"%d\" is ", x);
			
			if((x = Search(&s, &x)) == -1) {
				puts("nothing.");
				break;
			}
			switch (x) {
			 case 1:
				puts("the 1st from the top.");
				break;
			 case 2:
			 	puts("the 2nd from the top.");
			 	break;
			 case 3:
			 	puts("the 3rd from the top.");
			 	break;
			 default:
			 	printf("the %dth from the top.\n", x);
			}
		}

		puts("----------");
	}
	Terminate(&s);

	return 0;
}