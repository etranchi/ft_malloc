
#include "include/ft_malloc.h"

int main() {
	int i;
	char *addr;

	i = 0;
	while (i < 1024) {
		addr = (char *)malloc(sizeof(char) * 1024);
		addr[0] = 42;
		i++;
	}
	printf("yo\n");
	return (0);
}