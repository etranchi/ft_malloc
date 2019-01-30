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




t_block *initBlock(int size) {
	t_block b;

	b.size = size;
	b.ptr = (t_block *)mmap(0, SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	b.used = 1;
	b.next = NULL;
	return &b;
}

t_block *addBlock(t_block *ref, int size, int all_size) {
	t_block *b;
	if (all_size + size + sizeof(t_block) < SIZE) { 
		b->ptr = ref->ptr + size + sizeof(t_block);
		b->used = 1;
		b->size = size;
		b->next = NULL;
		return b;
	} else {
		b = initBlock(size);
		return b;
	}
};

void *addTo(t_block *tiny, int size) {
	t_block *tmp;
	int tmp_size;

	if (!tiny) {
		tiny = initBlock(size);
		return (void *)(tiny->ptr + sizeof(t_block));
	} else {
		tmp = tiny;
		while(tmp && tmp->next) {
			tmp_size += tmp->size + sizeof(t_block);
			tmp = tmp->next;

		}
		tmp->next = addBlock(tmp, size, tmp_size);
		return (void *)(tmp->next->ptr);
	}
}

void *ft_malloc(size_t size) {
	static t_container ctn;
	int i = 1;
	if (size <= 0) {
		return NULL;
	}
	if (size <= TINY) {
		return addTo(ctn.tiny, size);
	}
	else if (size <= SMALL) {
		return addTo(ctn.small, size);
	}
	else if (size > SMALL) {
		while (i * SIZE < size)
			i++;
		return addTo(ctn.large, (i - 1) * SIZE);
	}
	return NULL;
}