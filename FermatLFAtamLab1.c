#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LETTER_AMOUT 64

int main()
{
	int i, j, k;
	FILE *in;
	in = fopen("listnumber.txt", "w");
	if (in == NULL) {
		printf("fail to pen fail\n");
		exit(1);
	}
	for (i = 1; i <= LETTER_AMOUT; ++i) {
		for (j = i; j <= LETTER_AMOUT; ++j) {
			for (k = j; k <= LETTER_AMOUT; ++k) {
				fprintf(in,"%d + %d +%d = %.5lf\n",i,j,k, (pow(i, 3) + pow(j, 3) + pow(k, 3)) / 3);
			}
		}
	}
	return 0;
}