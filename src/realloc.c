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

# include "../include/ft_malloc.h"


static void *check_list(t_block **lst, void *ptr, size_t size) {
	t_block *tmp;
	t_block *ref;
	t_block *out;

	ref = *lst;
	tmp = *lst;
	while (tmp) {
		if (tmp->ptr == ptr) {
			if (size <= tmp->size) {
				if (!tmp->next) {
					tmp->size = size;
				}
				return ptr;
			} else {
				if (!tmp->next && ref + ref->all_size < tmp + size) {
					tmp->size = size;
					return ptr;
				} else {
					out = ft_memcpy(ft_malloc(size), tmp->ptr, tmp->size);
					ft_free(tmp->ptr);
					return out;
				}
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
	
}


void *ft_realloc(void *ptr, size_t size) {
	void *ret;

	printf("%p\n", ptr);
	if (!ptr) {
		printf("yo\n");
		return ft_malloc(size);
	}
	if ((ret = check_list(&(g_ctn).tiny, ptr, size))) {
		printf("yo1\n");
		return ret;
	}
	if ((ret = check_list(&(g_ctn).small, ptr, size))) {
		printf("yo2\n");
		return ret;
	}
	if ((ret = check_list(&(g_ctn).large, ptr ,size))) {
		printf("yo3\n");
		return ret;
	}

}