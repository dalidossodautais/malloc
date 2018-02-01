/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:05:37 by ddosso-d          #+#    #+#             */
/*   Updated: 2018/01/08 17:05:38 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	realloc_second(void *ptr, size_t size, t_page *page, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (i + j < page->space && i + j < size && page->empty[i] == EMPTY)
		++j;
	if (i + j >= size)
	{
		k = ptr - page->mem;
		while (++k < size)
			page->empty[k] = FILLED;
		while (k < i + j)
			page->empty[k++] = EMPTY;
		return (1);
	}
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	t_page	*page;
	void	*new;
	size_t	i;

	page = g_page;
	while (page && (ptr < page->mem || ptr >= page->mem + page->space))
		page = page->next;
	if (!page || (page->space <= SMALL &&
		!(page->empty[ptr - page->mem] & START)) || !size)
		return (0);
	i = ptr - page->mem;
	while (page->empty[i] & FILLED)
		++i;
	if (page->empty[i++] == EMPTY && page->space <= SMALL &&
		realloc_second(ptr, size, page, i))
		return (ptr);
	if (!(new = malloc(size)))
		return (0);
	((char *)new)[0] = ((char *)page->mem)[0];
	i = 0;
	while (++i < size && (page->empty[i] & FILLED))
		((char *)new)[i] = ((char *)page->mem)[i];
	free(ptr);
	return (new);
}
