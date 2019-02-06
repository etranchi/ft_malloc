/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:42:25 by etranchi          #+#    #+#             */
/*   Updated: 2019/01/29 11:42:26 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

static void			*check_list(t_block **lst, void *ptr, size_t size)
{
	t_block		*tmp;
	t_block		*ref;
	t_block		*out;

	ref = *lst;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->ptr == ptr)
			if (size <= tmp->size)
			{
				if (!tmp->next)
					tmp->size = size;
				return (ptr);
			}
			else
			{
				out = ft_memcpy(malloc(size), tmp->ptr,
					size > tmp->size ? tmp->size : size);
				free(tmp->ptr);
				return (out);
			}
		tmp = tmp->next;
	}
	return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
	void *ret;

	if (!ptr)
		return (malloc(size));
	if ((ret = check_list(&(g_ctn).tiny, ptr, size)))
		return (ret);
	if ((ret = check_list(&(g_ctn).small, ptr, size)))
		return (ret);
	if ((ret = check_list(&(g_ctn).large, ptr, size)))
		return (ret);
	return (NULL);
}
