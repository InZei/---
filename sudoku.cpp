//���������վ�
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<time.h>
using namespace std;
int mov[9] = { 0 };
int temp=0;
int er1[2][2] = { 3, 6, 6, 3 };
int er2[3] = { 1, 4, 7 };
int er3[3] = { 2, 5, 8 };
int chan[6][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 } };
int fr = (5 + 7) % 9 + 1;
int nown = 0;
int n = 1000000;
int vis[10] = { 0 };
FILE *fp = fopen("sudoku.txt", "w");
int map[9][9];

int judge(int num, int ple){
	int x = ple / 9;
	int y = ple % 9;
	int qulx = x / 3;
	int quey = y / 3;

	for (int i = 0; i < 9; i++){
		if (map[x][i] == num){
			return 0;
		}
	}

	for (int i = 0; i < 9; i++){
		if (map[i][y] == num){
			return 0;
		}
	}

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (map[qulx * 3 + i][quey * 3 + j] == num)
				return 0;
		}
	}
	return 1;
}

void getans(int next){
	if (temp == 1){
		return;
	}
	if (next == 81){
		char lis[600];
		temp = 1;
		int bi = 0;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (j == 0)lis[bi++] = map[i][j] + '0';
				else {
					lis[bi++] = ' ';
					lis[bi++] = map[i][j] + '0';
				}
			}
			lis[bi++] ='\n';
		}
		lis[bi++] = '\n';
		lis[bi] = '\0';
		fputs(lis, fp);
		return;
	}
	if (map[next / 9][next % 9] != 0){
		getans(next + 1);
		return;
	}

	for (int i = 1; i <= 9; i++){
		if (judge(i, next)){
			map[next / 9][next % 9] = i;
			getans(next + 1);
			map[next / 9][next % 9] = 0;
		}
	}
}

void makesudo(int list[9]){
	int lists[9];
	char lis[600];
	int bi = 0;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < mov[i]; j++){
			lists[mov[i] - 1 - j] = list[8 - j];
		}
		for (int j = 0; j < 9 - mov[i]; j++){
			lists[j + mov[i]] = list[j];
		}
		for (int j = 0; j < 9; j++){
			if (j == 0) lis[bi++] = lists[j] + '0';
			else{
				lis[bi++] = ' ';
				lis[bi++] = lists[j] + '0';
			}
		}
		lis[bi++] = '\n';
	}
	lis[bi++] = '\n';
	lis[bi] = '\0';
	nown++;
	fputs(lis, fp);
	if (nown == n){
		return;
	}
}

void makemov(int list[9]){
	mov[0] = 0;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 6; j++){
			for (int k = 0; k < 6; k++){
				for (int a = 0; a < 2; a++){
					mov[1+a] = er1[i][a];
				}
				for (int a = 0; a < 3; a++){
					mov[3+a] = er2[chan[j][a]];
				}

				for (int a = 0; a < 3; a++){
					mov[6+a] = er3[chan[k][a]];
				}
				
				makesudo(list);
				
				if (nown == n){
					goto part1;
				}
			}
		}
	}
part1:return;
}

int num(char c[]){
	int len = strlen(c);
	int s = 0;
	int jin = 1;
	for (int i = len - 1; i >= 0; i--){
		if (c[i]>'9' || c[i] < '0')return -1;
		s += (c[i] - '0')*jin;
		jin *= 10;
	}
	return s;
}

void dfs(int list[9],int x){
	if (nown == n){
		return;
	}
	if (x == 9){
		makemov(list);
		//fprintf(fp, "\n");
		return;
	}

	for (int i = 1; i <= 9; i++){
		if (vis[i] == 0){
			list[x] = i;
			vis[i] = 1;
			dfs(list, x + 1);
			vis[i] = 0;
		}
	}
	return;
}
int main(int argc, char *argv[]){
	clock_t start;
	start = clock();
	
	if (argc != 3){
		printf("WRONG TEXT!\n");
		return 0;
	}
	/*char argv1[10][1000] = { '\0' };

	scanf("%s", argv1[0]);
	scanf("%s", argv1[1]);
	scanf("%s", argv1[2]);*/
	if (!strcmp(argv[1], "-c")){
		n = num(argv[2]);
		if (n == -1){
			printf("WRONG TEXT!\n");
			return 0;
		}
		int list[9] = { fr, 0, 0, 0, 0, 0, 0, 0, 0 };
		vis[fr] = 1;
		//���57
		dfs(list, 1);
		fclose(fp);
		clock_t over;
		over = clock();
		printf("Time:%lf\n", double(over - start)/1000);
	}
	else if (!strcmp(argv[1], "-s")){
		FILE *fpRead = fopen(argv[2], "r");
		if (fpRead==NULL){
			printf("NO question\n");
			return 0;
		}
		
		while (fscanf(fpRead, "%d", &map[0][0])!=EOF){
			temp = 0;
			for (int i = 0; i < 9; i++){
				for (int j = 0; j < 9; j++){
					if (i == 0 && j == 0)continue;
					fscanf(fpRead, "%d", &map[i][j]);
				}
			}
			getans(0);
		}
		clock_t over;
		over = clock();
		printf("Time:%lf\n", double(over - start)/1000);
	}

	
}