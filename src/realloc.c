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

void				*replace(size_t size, t_block *tmp)
{
	void		*tmp_ptr;
	t_block		*out;

	if (!(tmp_ptr = malloc(size)))
		return (NULL);
	out = ft_memcpy(tmp_ptr, tmp->ptr,
		size > tmp->size ? tmp->size : size);
	free(tmp->ptr);
	return (out);
}

static void			*check_list(t_block **lst, void *ptr, size_t size)
{
	t_block		*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			if (size <= tmp->size)
			{
				if (!tmp->next)
					tmp->size = size;
				return (ptr);
			}
			else
				return (replace(size, tmp));
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
