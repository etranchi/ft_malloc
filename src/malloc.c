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
	static int		j = 0;

	i = 1;
	j++;
	while (i * SIZE < block_size + sizeof(t_block))
		i++;
	b = (t_block *)mmap(0, i * SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE, 0, 0);
	if (b == MAP_FAILED)
	{
		ft_printf("MAP FAILED\n");
		exit(0);
	}
	b->ptr = (void *)b + sizeof(t_block);
	b->size = data_size;
	b->all_size = (i * SIZE) - data_size - sizeof(t_block);
	b->used = 1;
	b->next = NULL;
	return (b);
}

t_block			*add_block(t_block *ref, int data_size, int block_size)
{
	t_block *b;

	if (data_size + sizeof(t_block) < ref->all_size)
	{
		b = (void *)ref->ptr + ref->size;
		b->ptr = (void *)b + sizeof(t_block);
		b->used = 1;
		b->size = data_size;
		b->all_size = ref->all_size - data_size - sizeof(t_block);
		b->next = NULL;
		return (b);
	}
	else
	{
		return (init_block(block_size, data_size));
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
		return (void *)(tmp->next->ptr);
	}
	else
	{
		*tiny = init_block(block_size, data_size);
		return ((void *)((*tiny)->ptr));
	}
}

void			*malloc(size_t size)
{
	static int first_time = 0;

	if (size <= 0)
		return (NULL);
	if (first_time == 0)
	{
		g_ctn.tiny = NULL;
		g_ctn.small = NULL;
		g_ctn.large = NULL;
		first_time = 1;
	}
	if (size < TINY)
		return (add_to(&(g_ctn).tiny, 100 * (TINY + sizeof(t_block)), size));
	else if (size < SMALL)
		return (add_to(&(g_ctn).small, 100 * (SMALL + sizeof(t_block)), size));
	else
		return (add_to(&(g_ctn).large, size, size));
	return (NULL);
}
