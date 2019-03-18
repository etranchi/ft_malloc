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

#include "../include/ft_malloc.h"

t_block			*init_block(int block_size, int data_size)
{
	t_block			*b;
	int				i;
	int				j;

	i = 1;
	j++;
	while (i * SIZE < block_size + sizeof(t_block))
		i++;
	b = (t_block *)mmap(0, i * SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE, 0, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->ptr = (void *)b + sizeof(t_block);
	j = -1;
	while (++j * 16 < data_size)
		;
	b->size = j * 16;
	b->all_size = (i * SIZE) - b->size - sizeof(t_block);
	b->used = 1;
	b->next = NULL;
	return (b);
}

t_block			*add_block(t_block *ref, int data_size, int block_size)
{
	t_block *b;
	t_block *tmp;
	int		i;

	i = -1;
	if (data_size + sizeof(t_block) < ref->all_size)
	{
		b = (void *)ref->ptr + ref->size;
		b->ptr = (void *)b + sizeof(t_block);
		b->used = 1;
		while (++i * 16 < data_size)
			;
		b->size = i * 16;
		b->all_size = ref->all_size - b->size - sizeof(t_block);
		b->next = NULL;
		return (b);
	}
	else
	{
		tmp = init_block(block_size, data_size);
		return (tmp != NULL ? tmp : NULL);
	}
}

void			*add_to(t_block **tiny, int block_size, int data_size)
{
	t_block		*tmp;
	t_block		*ref;

	if (*tiny)
	{
		tmp = *tiny;
		ref = *tiny;
		while (tmp && tmp->next)
		{
			if (!tmp->used && tmp->size >= data_size)
			{
				tmp->used = 1;
				return (tmp->ptr);
			}
			tmp = tmp->next;
		}
		tmp->next = add_block(tmp, data_size, block_size);
		return (tmp->next != NULL ? (void *)(tmp->next->ptr) : NULL);
	}
	else
	{
		*tiny = init_block(block_size, data_size);
		return ((*tiny) != NULL ? (void *)(*tiny)->ptr : NULL);
	}
}

void			*malloc(size_t size)
{
	static int first_time = 0;

	if (first_time == 0)
	{
		g_ctn.tiny = NULL;
		g_ctn.small = NULL;
		g_ctn.large = NULL;
		first_time = 1;
	}
	if ((int)size <= 0)
		return (NULL);
	if (size < TINY)
		return (add_to(&(g_ctn).tiny, 100 * (TINY + sizeof(t_block)), size));
	else if (size < SMALL)
		return (add_to(&(g_ctn).small, 100 * (SMALL + sizeof(t_block)), size));
	else
		return (add_to(&(g_ctn).large, size, size));
	return (NULL);
}
