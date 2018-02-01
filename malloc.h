/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:29:10 by ddosso-d          #+#    #+#             */
/*   Updated: 2018/01/05 15:29:12 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

# define TINY 64
# define SMALL 256
# define SPACE(x) ((x) <= TINY ? TINY : ((x) <= SMALL ? SMALL : (x)))
# define SPACE_CHAR(x) ((x) <= TINY ? "TINY" : ((x) <= SMALL ? "SMALL" : "LARGE"))
# define EMPTY 0
# define FILLED 1
# define START 2
# define HISTORIC 1
# define DUMP 2
# define MEM_ALLOC 4
# define HEXA "0123456789abcdef"

typedef struct s_page	t_page;

struct			s_page
{
	size_t	space;
	void	*mem;
	char	empty[SMALL];
	t_page	*next;
};

t_page			*g_page;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);
void			show_alloc_mem_ex(int bonus);

#endif
