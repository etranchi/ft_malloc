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


static t_block *list_tiny = NULL;
static t_block *list_small = NULL;
static t_block *list_large = NULL;


void *ft_malloc(size_t size) {
	void *ptr;
	size_t offset;
	
	offset = 0;
	if (list_tiny) {
		printf("yoooooo\n");
		ptr = list_tiny->page;
		offset = list_tiny->size;
	}
	if (size <= 0) {
		return NULL;
	}
	if (size <= SIZE) {

		if (!list_tiny && offset + size < SIZE) {
			ptr = mmap(ptr, SIZE, PROT_READ| PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, offset);
			if (ptr == MAP_FAILED) {
				printf("failed to map\n");
				return NULL;
			}
			printf("good map\n");
			return ptr;
		}
		else if (list_tiny && offset + size < SIZE) {
			printf("je passe ici\n");
			return ((void *)ptr + offset);
		}

	}
	return NULL;
}