#include<stdio.h>

int main(void){
	int i,j;
	unsigned char reg[4],c[4],out[15],dif[15];
	unsigned char output;
	int correlation;
	
	
	reg[0] = 1;
	reg[1] = 0;
	reg[2] = 0;
	reg[3] = 0;
	c[0] = 1;
	c[1] = 1;
	c[2] = 0;
	c[3] = 0;
	
	printf("■ 周期15のM系列ランダムビット列を作成します\n");
	printf("初期値：(%d,%d,%d,%d)\n",reg[3],reg[2],reg[1],reg[0]);
	printf("原子多項式：(1,%d,%d,%d,%d)\n",c[3],c[2],c[1],c[0]);
	printf("ビット列: ");
	
	for(i = 0; i<15; ++i){
		output = reg[3];
		for(j = 3; j>0; --j){
			reg[j] = reg[j-1];
		}
		reg[0] = 0;
		for(j=3; j>=0; --j){
			reg[j] ^= (c[j] & output);
		}

		out[i] = output;
		printf("%d",out[i]);
	}
	printf("\n");
	
	/* 自己相関求める */
	printf("■ 自己相関\n");
	for(i = 0; i<15; i++) {
		correlation = 0;
		printf("%dビットずらした時：",i);
			if(i<10) printf(" ");	/* 表示を整えるための操作 */
	
		/* dif[] iビット左シフト */
		for(j = 0; j<15; j++){
			if (j-i >= 0){
				dif[j] = out[j-i];
			} else {
				dif[j] = out [15 - i + j];	/* 15は 配列の長さ */
			}
			printf("%d",dif[j]);
		}
		
		/* out[]とdif[]の差分とる */
		for(j = 0; j<15; j++){
			if(out[j] - dif[j] == 0){
				correlation += 1;
			} else {
				correlation -= 1;
			}
		}
		printf("	自己相関：%d\n", correlation);
	}
		
	
	return 0;
}