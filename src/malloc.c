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
//
// 		exit(0);
// 	}
// 	page.mallocs = NULL;
// 	page.next = NULL;
// 	return &page;
// }

void 		show_alloc_mem() 
{
	t_block *tiny;
	t_block *small;
	t_block *large ;
	int total;

	tiny = g_ctn.tiny;
	small = g_ctn.small;
	large = g_ctn.large;
	total = 0;
	while (tiny) {
		if (tiny->used) {
			printf("%p - %p : %d octets\n", tiny->ptr, (tiny->ptr + tiny->size ), tiny->size);
			total += tiny->size;
		}
		tiny = tiny->next;
	}
	while (small) {
		printf("%p - %p : %d octets\n", small->ptr, small->ptr + small->size, small->size);
		total += small->size;
		small = small->next;
	}

	while (large) {
		// if (large->used) {
			printf("%p - %p : %d octets\n", large->ptr, large->ptr + large->size, large->size);
			total += large->size;
		// /}
		large = large->next;
	}
}


t_block 	*initBlock(int block_size, int data_size) 
{
	t_block *b;
	int i;
	static int j = 0;

	i = 1;
	j++;
	while (i * SIZE < block_size)
		i++;
	printf("%d\n", j);
	b = (t_block *)mmap(0, i * SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (b == MAP_FAILED) {
		printf("MAP FAILED\n");
		exit(0);
	}
 	b->ptr =(void *)b + sizeof(t_block);
 	b->size = data_size;
 	b->all_size = (i * SIZE) - data_size - sizeof(t_block);
	b->used = 1;
	b->next = NULL;
	return (b);
}

t_block 	*addBlock(t_block *ref, int data_size, int block_size) 
{
	t_block *b;

	if (data_size + sizeof(t_block) < ref->all_size) { 
		b = (void *)ref->ptr + ref->size;
		b->ptr = (void *)b + sizeof(t_block);
		b->used = 1;
		b->size = data_size;
		b->all_size = ref->all_size - data_size - sizeof(t_block);
		b->next = NULL;
		return (b);
	} else {
		return (initBlock(block_size, data_size));
	}
};

void 		*addTo(t_block **tiny, int block_size, int data_size) 
{
	t_block 	*tmp;
	t_block 	*ref;

	if (*tiny) {
		tmp = *tiny;
		ref = *tiny;
		while(tmp && tmp->next) {
			if (!tmp->used && tmp->size >= data_size) {
				tmp->used = 1;
				return tmp->ptr;
			}
			tmp = tmp->next;
		}
		tmp->next = addBlock(tmp, data_size, block_size);
		return (void *)(tmp->next->ptr);
	} else {
		*tiny = initBlock(block_size, data_size);
		return ((void *)((*tiny)->ptr));
	}
}

void 		*ft_malloc(size_t size) 
{
	static int first_time = 0;

	if (size <= 0)
		return (NULL);
	if (first_time == 0) {
		g_ctn.tiny = NULL;
		g_ctn.small = NULL;
		g_ctn.large = NULL;
		first_time = 1;
	}
	if (size < TINY) {
		return (addTo(&(g_ctn).tiny,  100 * (TINY + sizeof(t_block)), size));
	}
	else if (size < SMALL)
		return (addTo(&(g_ctn).small, 100 * (SMALL + sizeof(t_block)), size));
	else {
		return (addTo(&(g_ctn).large, size , size));
	}
	return (NULL);
}