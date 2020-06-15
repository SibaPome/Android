#include <stdio.h>
#define QSIZE 64
int square[8][8] = { {-1,-1,-1,-1,-1,-1,-1,-1},
					 					 {-1,0 ,0 ,0 ,0 ,0 ,0 ,-1},
					 				 	 {-1,0 ,0 ,-1,-1,-1,-1,-1},
					 				 	 {-1,0 ,-1,0 ,0 ,0 ,0 ,-1},
					 				 	 {-1,0 ,-1,0 ,0 ,0 ,0 ,-1},
					 				 	 {-1,0 ,-1,-1,-1,0 ,0 ,-1},
					 				 	 {-1,0 ,0 ,0 ,0 ,0 ,0 ,-1},
					 				 	 {-1,-1,-1,-1,-1,-1,-1,-1},
									 	};

struct position{	/* マス目の位置を示す */
	int raw;
	int column;
};
struct position queue[QSIZE];	/* 待ち行列 */
int front = 0;			/* 待ち行列の先頭 */
int rear = 0;				/* 待ち行列の最後尾 */

void view(int[][8]);						/* プロトタイプ宣言 */
void enqueue(struct position);
struct position deque(void);
int empty_check(void);

int main (void){
	struct position start,goal;		/* 開始地点と終了地点のマスを表す構造体 */
	struct position right,left,up,down;

	printf("\n");
	view(square);
	printf("\n");

	char buf[256];
	do{
		printf("Choose two squares. (EX) (2,4),(4,5)\n");
		fgets(buf,sizeof(buf),stdin);
		sscanf(buf,"(%d,%d),(%d,%d)", &start.raw,&start.column,&goal.raw,&goal.column);
	}while(square[start.raw-1][start.column-1] != 0 || square[goal.raw-1][goal.column-1] != 0);	/* 有効な入力があるまで繰り返す */

	printf("\n");
	printf("Start:	(%d,%d)\n",start.raw,start.column);
	printf("Goal:	(%d,%d)\n",goal.raw,goal.column);
	printf("\n");

	start.raw--,start.column--,goal.raw--,goal.column--;		/* マスの位置ずれを直す */
	square[start.raw][start.column] = 1;
	square[goal.raw][goal.column] = -2;

	view(square);						/* スタートとゴールの位置を加えて示す */
	square[goal.raw][goal.column] = 0;

	/* ここから探索部（キューを用いた幅探索） */
	enqueue(start);
	while(empty_check() != 1){
		start = deque();
		if(square[start.raw][start.column+1]==0){
			square[start.raw][start.column+1] = square[start.raw][start.column] + 1;
			right.raw = start.raw;
			right.column = start.column + 1;
			enqueue(right);
		}
		if(square[start.raw][start.column-1]==0){
			square[start.raw][start.column-1] = square[start.raw][start.column] + 1;
			left.raw = start.raw;
			left.column = start.column - 1;
			enqueue(left);
		}
		if(square[start.raw-1][start.column]==0) {
			square[start.raw-1][start.column] = square[start.raw][start.column] + 1;
				up.raw = start.raw -1;
				up.column = start.column;
				enqueue(up);
			}
		if(square[start.raw+1][start.column]==0) {
			square[start.raw+1][start.column] = square[start.raw][start.column] + 1;
				down.raw = start.raw +1;
				down.column = start.column;
				enqueue(down);
			}
		}

		printf("Distance to goal :	%d\n",square[goal.raw][goal.column]-1);
		return 0;
}

void view(int matrix[][8]){				/* マス目を表示 */
	int i,k;
	for(i = 0; i<8 ; i++){
		for(k = 0 ; k<8 ; k++){
			if(square[i][k] == -1)						 printf("* ");
			else if(square[i][k] == 0)				 printf("  ");
			else if(square[i][k] == 1)				 printf("S ");
			else															 printf("G ");

			if(k == 7)	printf("\n");
		}
	}
}

void enqueue(struct position data){		/* キューにデータを追加 */
	queue[rear++] = data;
}

struct position deque(void){	/* キューの先頭からデータ取り出し */
	return queue[front++];
}

int empty_check(void){		/* キューが空なら1，それ以外は0を出力 */
		return (front == rear);
}
