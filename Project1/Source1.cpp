#include <iostream>
#include <cstdio>

using namespace std;

int main4(void) {
	int a = 10, b= 9, c = 8;
	c = (a -= (b - 5));

	printf("%d", c);

	return 0;
}
