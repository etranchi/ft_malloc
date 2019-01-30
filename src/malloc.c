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


t_page *initPage(int size) {
	t_page page;

	page.data = mmap(0, SIZE, PROT_READ| PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (page.data == MAP_FAILED) {
		printf("failed to map\n");
		exit(0);
	}
	page.mallocs = NULL;
	page.next = NULL;
	return &page;
}

t_malloc *initMalloc(int size, int offset) {
	t_malloc malloc;

	malloc.size = size;
	malloc.offset = offset;
	malloc.next = NULL;
	return &malloc;
}

void *ft_malloc(size_t size) {
	static t_container ctn;

	if (size <= 0) {
		return NULL;
	}
	if (size <= TINY) {
		if (!ctn.tiny) {
			ctn.tiny = initPage(SIZE);
		}
		if (!ctn.tiny->mallocs) {
			ctn.tiny->mallocs = initMalloc(size, 0);
		}
		if (ctn.tiny->mallocs->offset + ctn.tiny->mallocs->size + size < SIZE) {
			return ctn.tiny->data + ctn.tiny->mallocs->offset + ctn.tiny->mallocs->size + size;
		}

	}
	return NULL;
}