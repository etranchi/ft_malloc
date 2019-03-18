/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:42:25 by etranchi          #+#    #+#             */
/*   Updated: 2019/01/29 11:42:26 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

int				check_this_map(t_block **lst, t_block *prev_ref, t_block *tmp_b)
{
	t_block		*tmp;
	t_block		*pre;
	int			tmp_size;
	int			lst_size;

	tmp = (*lst);
	pre = NULL;
	tmp_b->used = 0;
	lst_size = (*lst)->size + (*lst)->all_size + sizeof(t_block);
	tmp_size = tmp_size + sizeof(t_block);
	while (tmp && (void *)tmp + tmp_size < (void *)(*lst) + lst_size)
	{
		if (tmp->used)
			return (0);
		pre = tmp;
		tmp_size = tmp_size + sizeof(t_block);
		tmp = tmp->next;
	}
	if (pre->next && prev_ref)
		prev_ref->next = pre->next;
	munmap(&(*lst), lst_size);
	return (1);
}

void			change_value(t_block *prev_ref, t_block *tmp_prev,
	t_block *ref, t_block *tmp)
{
	prev_ref = tmp_prev;
	ref = tmp;
}

static int		check_list(t_block **lst, void *ptr)
{
	t_block		*tmp;
	t_block		*ref;
	t_block		*tmp_prev;
	t_block		*prev_ref;

	tmp = *lst;
	ref = *lst;
	prev_ref = *lst;
	while (tmp)
	{
		if ((void *)tmp + tmp->size + sizeof(t_block) >
			(void *)ref + ref->all_size + sizeof(t_block))
			change_value(prev_ref, tmp_prev, ref, tmp);
		if (tmp->ptr == ptr)
			if (check_this_map(&ref, prev_ref, tmp))
				if (ref == (*lst))
					*lst = NULL;
		if (tmp->ptr == ptr)
			return (1);
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void			free(void *ptr)
{
	if (!ptr)
		return ;
	if (check_list(&(g_ctn).tiny, ptr))
		return ;
	if (check_list(&(g_ctn).small, ptr))
		return ;
	if (check_list(&(g_ctn).large, ptr))
		return ;
}
