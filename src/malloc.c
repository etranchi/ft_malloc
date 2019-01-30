/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:42:15 by etranchi          #+#    #+#             */
/*   Updated: 2019/01/29 11:42:19 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/ft_malloc.h"


// t_page *initPage(int size) {
// 	t_page page;

// 	page.data = mmap(0, SIZE, PROT_READ| PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
// 	if (page.data == MAP_FAILED) {
// 		printf("failed to map\n");
// 		exit(0);
// 	}
// 	page.mallocs = NULL;
// 	page.next = NULL;
// 	return &page;
// }

void show_alloc_mem() {
	
	t_block *tiny = ctn.tiny;
	t_block *small = ctn.small;
	t_block *large = ctn.large;
	int total;

	printf("TINY : %p\n", &ctn.tiny);
	while (tiny) {
		printf("%p - %p : %d octets\n", tiny->ptr, (tiny->ptr + tiny->size ), tiny->size);
		total += tiny->size;
		tiny = tiny->next;
	}

	printf("SMALL :\n");
	while (small) {
		printf("%p - %p : %d octets\n", small->ptr, small->ptr + small->size, small->size);
		total += small->size;
		small = small->next;
	}

	printf("LARGE :\n");
	while (large) {
		printf("%p - %p : %d octets\n", large->ptr, large->ptr + large->size, large->size);
		total += large->size;
		large = large->next;
	}
}


t_block *initBlock(int size) {
	t_block *b;

	
	b = (t_block *)mmap(0, SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (b == MAP_FAILED) {
		printf("Error MAP\n");
		exit(0);
	}

 	b->ptr = b + sizeof(t_block);
 	b->size = size;
	b->used = 1;
	b->next = NULL;
	return b;
}

t_block *addBlock(t_block *ref, int size, int all_size) {
	t_block *b;

	printf("je suis la\n");
	if (all_size + size + sizeof(t_block) < SIZE) { 
		printf("j'ai de la place\n");
		b = ref->ptr + ref->size;
		printf("ref maillon\n");
		b->ptr = b + sizeof(t_block);
		printf("ref data\n");
		b->used = 1;
		b->size = size;
		b->next = NULL;
		return b;
	} else {
		printf("j'en ai pas\n");
		b = initBlock(size);
		return b;
	}
};

void *addTo(t_block **tiny, int size) {
	t_block *tmp;
	int tmp_size;
	printf("plouf\n");
	if (*tiny) {
		printf("oui\n");
		tmp = *tiny;
		while(tmp && tmp->next) {
			tmp_size += tmp->size + sizeof(t_block);
			tmp = tmp->next;
		}
		tmp->next = addBlock(tmp, size, tmp_size);
		return (void *)(tmp->next->ptr);
	} else {
		printf("non\n");
		*tiny = initBlock(size);
		return (void *)((*tiny)->ptr);
	}
}

void *ft_malloc(size_t size) {
	int i = 1;

	if (size <= 0) {
		return NULL;
	}
	if (size <= TINY) {
		printf("yoo\n");
		return addTo(&(ctn).tiny, size);
	}
	else if (size <= SMALL) {
		return addTo(&(ctn).small, size);
	}
	else if (size > SMALL) {
		while (i * SIZE < size)
			i++;
		return addTo(&(ctn).large, (i - 1) * SIZE);
	}
	return NULL;
}