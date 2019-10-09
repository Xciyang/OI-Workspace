#include <iostream>
#include <stdlib.h>
#include <time.h>
int tot;
int main() {
	std::cin >> tot;
	srand(20191009 + tot);
	std::cout << rand() % (tot - 1) + 2 << std::endl;
	return 0;
}