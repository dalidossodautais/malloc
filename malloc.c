/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:45:03 by ddosso-d          #+#    #+#             */
/*   Updated: 2018/01/13 11:45:05 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	fill_empty(t_page *new, size_t size)
{
	size_t	i;

	if (size <= SMALL)
	{
		new->empty[0] = (START | FILLED);
		i = 1;
		while (i < size)
			new->empty[i++] = FILLED;
		while (i < new->space)
			new->empty[i++] = EMPTY;
	}
}

void	*create_page(size_t size)
{
	t_page	*tmp;
	t_page	*new;

	if mmap(0, sizeof(t_page), PROT_WRITE,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0)))
		return (0);
	new->space = SPACE(size);
	if (!(new->mem = (void *)mmap(0, size, PROT_WRITE,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0)))
		return (0);
	new->next = 0;
	fill_empty(new, size)g_page;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!g_page)
		g_page = new;
	else
		tmp->next = new;
	return (new->mem);
}

void	*can_enter(t_page *page, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < page->space)
	{
		j = 0;
		while (i + j < page->space && j < size && page->empty[i + j] == FILLED)
			++j;
		if (j == size)
			break ;
		i += j + 1;
	}
	if (j == size)
		return (0);
	page->empty[i + j++] = (START | FILLED);
	j = 1;
	while (j < size)
		page->empty[i + j++] = FILLED;
	return (page->mem + i);
}

void	*malloc(size_t size)
{
	t_page	*page;
	void	*mem;

	if (!size)
		return (0);
	page = g_page;
	while (page)
	{
		if (size < SMALL && page->space == SPACE(size) &&
				(mem = can_enter(page, size)))
			return (mem);
		page = page->next;
	}
	return (create_page(size));
}
