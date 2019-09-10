#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char instr[256], instr2[256], instr3[256], flag, flag2;
int cnt;
int main() {
	scanf("%s", instr);
	if(strlen(instr) == 1) {
		cnt= instr[0] - '0';
		while(scanf("%s", instr3) > 0) {
			int i;
			for(i= 0; i < (int)strlen(instr3); i++)
				if(instr3[i] >= '0' && instr3[i] <= '9') break;
			for(int j= 0; j < i; j++) putchar(instr3[j]);
			printf("%d", cnt);
			for(int j= i; j < (int)strlen(instr3); j++)
				if(instr3[j] < '0' || instr3[j] > '9') putchar(instr3[j]);
			if(!flag)
				flag= 1, putchar(' ');
			else
				flag= 0, ++cnt, putchar('\n');
		}
	}
	else {
		scanf("%s", instr2);
		int i;
		for(i= 0; i < (int)strlen(instr); i++) {
			if(instr[i] >= '0' && instr[i] <= '9') flag2= 1, cnt= cnt * 10 + instr[i] - '0';
			if(instr[i] == '.') break;
		}
		if(!flag2)
			for(int j= i; j < (int)strlen(instr); j++)
				if(instr[j] >= '0' && instr[j] <= '9') cnt= cnt * 10 + instr[j] - '0';
		while(scanf("%s", instr3) > 0) {
			for(int j= 0; j < i; j++)
				if(instr[j] < '0' || instr[j] > '9') putchar(instr[j]);
			if(flag2) printf("%d", cnt);
			if(!flag) {
				for(int j= i; j < (int)strlen(instr); j++)
					if(instr[j] < '0' || instr[j] > '9') putchar(instr[j]);
			}
			else
				printf(".%s", instr2);
			if(!flag2) printf("%d", cnt);
			if(!flag)
				flag= 1, putchar(' ');
			else
				flag= 0, ++cnt, putchar('\n');
		}
	}
	return 0;
}