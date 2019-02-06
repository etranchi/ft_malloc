/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:38:15 by etranchi          #+#    #+#             */
/*   Updated: 2019/01/29 11:38:16 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

int main() {
	// printf("%d\n", getpagesize());
	int i = 0;
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp = (char*)ft_malloc(16);
	ft_free(NULL);
	ft_free((void *)tmp + 5);
	if (ft_realloc((void *)tmp + 5, 10) == NULL) {
		printf("Bonjours\n");
	}

	while ( i < 3){
		tmp = ft_malloc(sizeof(char) * 1024);

		i++;
	}
	show_alloc_mem();
}



/*****


malloc(5000)

alloue 2 

5000 / 100 

|[1]--[1]--[1]--[0]-- |



mallloc (3000)

cree un TINY */
