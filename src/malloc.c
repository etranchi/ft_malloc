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

	tiny = ctn.tiny;
	small = ctn.small;
	large = ctn.large;
	total = 0;
	printf("TINY : %p\n", &ctn.tiny);
	while (tiny) {
		printf("%p - %p : %d octets\n", tiny + sizeof(t_block), (tiny + sizeof(t_block) + tiny->size ), tiny->size);
		total += tiny->size;
		tiny = tiny->next;
	}

	printf("SMALL :\n");
	while (small) {
		printf("%p - %p : %d octets\n", small + sizeof(t_block), small + sizeof(t_block) + small->size, small->size);
		total += small->size;
		small = small->next;
	}

	printf("LARGE :\n");
	while (large) {
		printf("%p - %p : %d octets\n", large + sizeof(large), large + sizeof(t_block) + large->size, large->size);
		total += large->size;
		large = large->next;
	}

	printf("Total : %d octets\n", total);
}


t_block 	*initBlock(int size) 
{
	t_block *b;
	int i;

	i = 0;
	while(++i < SIZE)
		i++;
	b = (t_block *)mmap(0, i * SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (b == MAP_FAILED)
		exit(0);
 	b->ref = b;
 	b->size = size;
	b->used = 1;
	b->next = NULL;
	return (b);
}

t_block 	*addBlock(int size, int all_size) 
{
	t_block *b;

	if (all_size + size + sizeof(t_block) < SIZE) { 
		b = ctn.tiny + all_size;
		b->ref = ctn.tiny;
		b->used = 1;
		b->size = size;
		b->next = NULL;
		return (b);
	} else
		return (initBlock(size));
};

void 		*addTo(t_block **tiny, int size) 
{
	t_block 	*tmp;
	int			tmp_size;

	tmp_size = 0;
	if (*tiny) {
		tmp = *tiny;
		while(tmp && tmp->next) {
			tmp_size += tmp->size + sizeof(t_block) + 1;
			tmp = tmp->next;
		}
		tmp->next = addBlock(size, tmp_size != 0 ? tmp_size : tmp->size + sizeof(t_block));
		return (void *)(tmp->next + sizeof(t_block));
	} else {
		*tiny = initBlock(size);
		return ((void *)((*tiny) + sizeof(t_block)));
	}
}

void 		*ft_malloc(size_t size) 
{
	if (size <= 0)
		return (NULL);
	if (size <= TINY)
		return (addTo(&(ctn).tiny, size));
	else if (size <= SMALL)
		return (addTo(&(ctn).small, size));
	else if (size > SMALL) {
		return (addTo(&(ctn).large, size));
	}
	return (NULL);
}