/*
	演習:整合性判定
	演習「スタックの実装」で実装したスタックの機能を用いて
	整合性判定プログラムを作成する。
*/

#include <stdio.h>
#include <stdlib.h>

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

/* スタックは空か */
int IsEmpty(const Stack *s) {
	return (s->num <= 0);
}

/* 括弧の整合性判定関数 */
/* 戻り値...整合性が取れている:1/取れていない:0 */
int judgeConsistency(char *str) {
	Stack stk;
	char top, c;
	int i = 0;

	Initialize(&stk);
	while(str[i] != '\0') {
		/* 入力文字列を1文字ずつ調べる */
		switch(str[i]) {
		 /* 始め括弧のとき...それに対応する閉じ括弧をスタックにプッシュ */
		 case '(':
		 	Push(&stk, ')');
		 	break;
		 case '{':
		 	Push(&stk, '}');
		 	break;
		 case '[':
		 	Push(&stk, ']');
		 	break;

		 /* 
		 	閉じ括弧のとき...スタックが空もしくは整合性が取れていないときは0を返す
		 	整合性が取れたときはスタックから1つポップ
		 */
		 case ')':
		 case '}':
		 case ']':
		 	top = -1;
		 	Peek(&stk, &top);
		 	if(IsEmpty(&stk) || top != str[i])
		 		return 0;
		 	else
		 		Pop(&stk, &c);
		 	break;

		 default:
		 	break;
		}
		i++;
	}

	/* 文字列を全て見終わってスタックが空なら1 そうでなければ0を返す */
	if(IsEmpty(&stk))
		return 1;
	else
		return 0;
}

int main(void) {
	char str[101], c;
	int flag_continue = 1;
	int i;

	while (flag_continue == 1) {
		puts("-----");
		puts("括弧の整合性を判定します。");
		printf("文字列を入力してください（100文字以内） : ");
		/* 1行入力 空白を挟んだ文字列も入力可 */
		for (i = 0; i < 100 && (c = getchar()) != '\n'; ++i)
        	str[i] = c;
        while(c != '\n')	c = getchar();	// 100文字以上の文字列の除去
        str[i] = '\0';	// 末尾にヌル文字追加

		if(judgeConsistency(str)) {
			puts("この文字列は括弧の整合性が取れています。");
		} else {
			puts("この文字列は括弧の整合性がとれていません。");
		}

		printf("もう一度しますか（Yes:1 / No:1以外） : ");
		scanf("%d", &flag_continue);
		c = getchar();	// 改行文字の除去
	}

	return 0;
}