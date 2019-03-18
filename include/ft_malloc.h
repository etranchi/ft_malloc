/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:38:05 by etranchi          #+#    #+#             */
/*   Updated: 2019/01/29 11:38:06 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

# include "../lib/ft_printf/ft_printf.h"

# define SIZE 4096
# define TINY 512
# define SMALL SIZE

typedef struct		s_block
{
	void			*ptr;
	int				used;
	int				size;
	int				all_size;
	struct s_block	*next;
}					t_block;

typedef struct		s_container
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_container;

t_container			g_ctn;

int					ft_printf(const char *format, ...);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

#endif
