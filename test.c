
#include "include/ft_malloc.h"


int main() {
	void *ptr;

	malloc(20000);
	malloc(20000);
	malloc(20000);
	ptr = malloc(12099);
	malloc(20000);
	malloc(20000);
	malloc(2000000000);
	//realloc(ptr + 2, 22);
	//malloc(32);
	//ptr = malloc(533300);
	free(ptr);
	show_alloc_mem();
	return (0);
}