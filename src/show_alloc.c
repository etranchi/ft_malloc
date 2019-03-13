/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:18:40 by etranchi          #+#    #+#             */
/*   Updated: 2019/02/06 14:18:42 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

int				show_list(t_block **lst, char *type)
{
	t_block		*tmp;
	int			total;

	tmp = *lst;
	total = 0;
	ft_printf("%s : %p \n", type, tmp);
	while (tmp)
	{
		if (tmp->used) {
			ft_printf("%p - %p : %lu octets\n",
				tmp->ptr, (tmp->ptr + tmp->size), tmp->size);
			total += tmp->size;
		}
		tmp = tmp->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	int		total;

	total = 0;
	total += show_list(&g_ctn.tiny, "TINY");
	total += show_list(&g_ctn.small, "SMALL");
	total += show_list(&g_ctn.large, "LARGE");
	ft_printf("Total : %lu octets\n", total);
	return ;
}
