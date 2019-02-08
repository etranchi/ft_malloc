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

void			check_this_map(t_block **lst, t_block *prev, t_block **g_ref)
{
	t_block		*tmp;
	t_block		*pre;
	void		*offset;

	tmp = *lst;
	pre = NULL;
	while (tmp)
	{
		if (tmp < (*lst) || tmp > (*lst) + (*lst)->all_size)
			break ;
		if (tmp->used)
			return ;
		pre = tmp;
		tmp = tmp->next;
	}
	if ((*lst) != *g_ref)
	{
		if (pre->next && prev)
			prev->next = pre->next;
		if (munmap(&(*lst), (*lst)->all_size))
			ft_printf("success munmap\n");
		else
			ft_printf("error munmap\n");
	}
}

void			check_munmap(t_block **lst, t_block *prev, t_block **ref)
{
	t_block		*tmp;
	void		*tmp_size;

	tmp = *lst;
	while (tmp)
	{
		tmp_size = (void *)tmp + tmp->all_size + sizeof(t_block);
		if (tmp >= *lst && tmp_size < (void *)(*lst))
			check_this_map(&tmp, prev, ref);
		else
			return ;
		prev = tmp;
		tmp = tmp->next;
	}
}

static int		check_list(t_block **lst, void *ptr)
{
	t_block		*tmp;
	t_block		*ref;

	tmp = *lst;
	ref = *lst;
	while (tmp)
	{
		if ((void *)tmp > (void *)ref + ref->all_size || tmp < ref)
			ref = tmp;
		if (tmp->ptr == ptr)
		{
			tmp->used = 0;
			check_munmap(&tmp, ref, lst);
			return (1);
		}
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
