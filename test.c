
#include "include/ft_malloc.h"


int main() {
	void *ptr;

	malloc(200);
	malloc(53);
	malloc(22);
	ptr = malloc(11);
	realloc(ptr, 22);
	malloc(32);
	malloc(533300);
	free(ptr);
	show_alloc_mem();
	return (0);
}