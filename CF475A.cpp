#include <iostream>
#include <stdio.h>
using namespace std;
int n;
char bus[][28]= {"+------------------------+ ", "|#.#.#.#.#.#.#.#.#.#.#.|D|)", "|#.#.#.#.#.#.#.#.#.#.#.|.| ", "|#.......................| ", "|#.#.#.#.#.#.#.#.#.#.#.|.|)", "+------------------------+ "};
int main() {
	cin >> n;
	for(int i= 0; i < 28; i++)
		for(int j= 0; j < 6; j++)
			if(bus[j][i] == '#' && n) --n, bus[j][i]= 'O';
	for(int i= 0; i < 6; i++) {
		for(int j= 0; j < 27; j++)
			if(bus[i][j] != ' ') putchar(bus[i][j]);
		if(i != 5) putchar('\n');
	}
	return 0;
}