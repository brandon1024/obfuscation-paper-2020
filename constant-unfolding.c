#include <stdio.h>

int main(void)
{
	int a = 116;
	int b = (((a + 0x8f63) << 3) - (0x47b18)) >> 2;
	
	printf("%d\n", b);
	return 0;
}

