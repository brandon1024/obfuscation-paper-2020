#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int r = 1, e = 12, a = argc;
	do {
		if (e & 1)
			r *= a;

		e >>= 1;
		if (e)
			a *= a;
	} while (e);

	int len = (r % 13) * 617 + 407;
	printf("%d\n", len);

	return 0;
}
