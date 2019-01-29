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
	char *tmp = ft_malloc(sizeof(char) * 1025);
	tmp= "coucou";

	printf("%s\n", tmp);

	char *tmp1 = ft_malloc(sizeof(char) * 1025);

	tmp1= "poualalalala"; 

	printf("%s\n", tmp1);

		char *tmp2 = ft_malloc(sizeof(char) * 1025);

	tmp2= "poualalalala1"; 

	printf("%s\n", tmp2);

		char *tmp3 = ft_malloc(sizeof(char) * 1025);

	tmp3= "poualalalala2"; 

	printf("%s\n", tmp3);
}



/*****


malloc(5000)

alloue 2 

5000 / 100 

|[1]--[1]--[1]--[0]-- |



mallloc (3000)

cree un TINY */
