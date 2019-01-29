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

# include "../lib/libft/libft.h"

# define SIZE getpagesize()
# define TINY 1024
# define SMALL 4096
# define LARGE 4097

typedef struct s_block 
{
	off_t 	size;
	void 	*page;
}				t_block;

void 	ft_free(void *ptr);
void 	*ft_malloc(size_t size);
void 	*ft_realloc(void *ptr, size_t size);


#endif
