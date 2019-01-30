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
	printf("%d\n", getpagesize());
	int i = -1;

	while (++i < 100) {
		char *tmp = ft_malloc(sizeof(char) * 5000);
		tmp= "coucou";
		printf("%s\n", tmp);
	}

	while (++i < 100) {
		char *tmp = ft_malloc(sizeof(char) * 5000);
		tmp= "coucou";
		printf("%s\n", tmp);
	}

	while (++i < 100) {
		char *tmp = ft_malloc(sizeof(char) * 5000);
		tmp= "coucou";
		printf("%s\n", tmp);
	}
}



/*****


malloc(5000)

alloue 2 

5000 / 100 

|[1]--[1]--[1]--[0]-- |



mallloc (3000)

cree un TINY */
