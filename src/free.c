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

# include "../include/ft_malloc.h"


int check_list(t_block **lst, void *ptr) {
	t_block *tmp;
	t_block *ref;
	int offset;

	ref = *lst;
	tmp = *lst;
	while (tmp) {
		if (ref->ref != tmp->ref) {

		}
		tmp = tmp->next;
	}
}

void free(void *ptr) {
	if (!ptr) {
		return ;
	}
	if (check_list(&(ctn).tiny, ptr)) {
		return ;
	}
	if (check_list(&(ctn).small, ptr)) {
		return ;
	}
	if (check_list(&(ctn).large, ptr)) {
		return ;
	}
}