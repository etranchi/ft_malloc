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

size_t			ft_nbrlen(int n, unsigned int base)
{
	size_t		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static void		ft_print_mem(uintmax_t n, size_t base)
{
	char				str[ft_nbrlen(n, base)];
	size_t				len;

	len = ft_nbrlen(n, base) - 1;
	if (n == 0)
		str[len] = '0';
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (base > 10 && n % base > 9) ?
			(n % base) + ('a' - 10) : (n % base) + 48;
		n /= base;
		len--;
	}
	ft_putstr(str);
}

static void		ft_print_all(t_block *malloc)
{
	ft_putstr("0x");
	ft_print_mem((uintmax_t)malloc->ptr, 16);
	ft_putstr(" - 0x");
	ft_print_mem((uintmax_t)malloc->ptr + malloc->size, 16);
	ft_putstr(" : ");
	ft_print_mem((uintmax_t)malloc->size, 10);
	ft_putstr(" octets\n");
}

int				show_list(t_block **lst, char *type)
{
	t_block		*tmp;
	size_t		total;
	void		*tmp_ptr;

	tmp = *lst;
	total = 0;
	if (tmp)
	{
		ft_putstr(type);
		ft_putstr(" : 0x");
		ft_print_mem((unsigned long long)tmp, 16);
		ft_putstr(" \n");
	}
	while (tmp != NULL)
	{
		if (tmp && tmp->used)
		{
			ft_print_all(tmp);
			total += tmp->size;
		}
		tmp = tmp->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	total += show_list(&g_ctn.tiny, "TINY");
	total += show_list(&g_ctn.small, "SMALL");
	total += show_list(&g_ctn.large, "LARGE");
	ft_putstr("Total : ");
	ft_putstr(ft_itoa(total));
	ft_putstr(" octets\n");
	return ;
}
