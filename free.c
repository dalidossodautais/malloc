/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:49:55 by ddosso-d          #+#    #+#             */
/*   Updated: 2018/01/05 19:49:57 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	remove_mem(t_page *page)
{
	t_page	*prev;

	munmap(page->mem, page->space);
	if (g_page == page)
	{
		munmap(page, sizeof(page));
		g_page = 0;
		return ;
	}
	prev = (t_page *)g_page;
	while (prev->next != page)
		prev = prev->next;
	munmap(page, sizeof(page));
	page = 0;
	prev->next = 0;
}

void	free(void *ptr)
{
	t_page	*page;
	size_t	i;

	page = g_page;
	while (page)
	{
		if (ptr >= page->mem && ptr < page->mem + page->space)
			break ;
		page = page->next;
	}
	if (!page || !(page->empty[ptr - page->mem] & START))
		return ;
	i = ptr - page->mem;
	while (page->empty[i] & FILLED)
		page->empty[i++] = EMPTY;
	i = 0;
	while (i < page->space && page->empty[i] == EMPTY)
		++i;
	if (i == page->space)
		remove_mem(page);
}
