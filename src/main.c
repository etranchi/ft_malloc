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
	
	while (i < 1024) {
		// tmp = (char *)malloc(1024);
		// tmp[0] = 42;

		i++;
		// ft_free(tmp);
	}
	// show_alloc_mem();
	// tmp1 = NULL;
	// char *yo = ft_realloc(tmp1, 5004);
	// show_alloc_mem();
	// while (++i < 2) {
		
	// 	ft_free(ft_malloc(sizeof(char) * (39 - i)));
	// 	show_alloc_mem();
	// }
		

	// i = 0;
	// while (++i < 100) {
	// 	char *tmp = ft_malloc(sizeof(char) * 399);
	// 	tmp= "small";
	// 	printf("%s\n", tmp);
	// }
	// i = 0;
	// while (++i < 2) {
	// 	ft_free(ft_malloc(sizeof(char) * 5000));
	// 	show_alloc_mem();
	// }

	


}



/*****


malloc(5000)

alloue 2 

5000 / 100 

|[1]--[1]--[1]--[0]-- |



mallloc (3000)

cree un TINY */
