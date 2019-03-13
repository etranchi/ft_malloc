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

int				check_this_map(t_block **lst, t_block *prev_ref)
{
	t_block		*tmp;
	t_block		*pre;
	void		*offset;

	tmp = *lst;
	pre = NULL;
	while (tmp && (void *)tmp + tmp->size + sizeof(t_block) < (void *)(*lst) + (*lst)->size + (*lst)->all_size + sizeof(t_block))
	{
		if (tmp->used)
			return (0);
		pre = tmp;
		tmp = tmp->next;
	}
	if (pre->next && prev_ref)
		prev_ref->next = pre->next;
	munmap(&(*lst), (*lst)->all_size + (*lst)->size + sizeof(t_block));
	*lst = NULL;
	return (1);
}

// void			check_munmap(t_block **lst, t_block *prev, t_block **ref)
// {
// 	t_block		*tmp;
// 	void		*tmp_size;

// 	tmp = *lst;

// 	while (tmp)
// 	{
// 		if (tmp->ptr + tmp->all_size + sizeof(t_block) > (*lst)->ptr + (*lst)->all_size) {
// 			if (check_this_map(&tmp, prev, ref)) 
// 				return ;
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// }

static int		check_list(t_block **lst, void *ptr)
{
	t_block		*tmp;
	t_block		*ref;
	t_block		*tmp_prev;
	t_block		*prev_ref;

	tmp = *lst;
	ref = *lst;
	while (tmp)
	{
		if ((void *)tmp + tmp->size + sizeof(t_block) > (void *)ref + ref->all_size + sizeof(t_block)) {
			prev_ref = tmp_prev;
			ref = tmp;
		}
		if (tmp->ptr == ptr)
		{
			tmp->used = 0;
			check_this_map(&ref, prev_ref);
			return (1);
		}
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
