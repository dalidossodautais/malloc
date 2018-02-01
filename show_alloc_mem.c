/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 11:54:26 by ddosso-d          #+#    #+#             */
/*   Updated: 2018/01/08 11:54:27 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_hexa(unsigned long n)
{
	if (n / 16)
		print_hexa(n / 16);
	write(1, &HEXA[n % 16], 1);
}

void	print_nbr(unsigned long n)
{
	if (n / 10)
		print_hexa(n / 10);
	while (n >= 10)
		n -= 10;
	write(1, &HEXA[n], 1);
}

void	print_space(t_page *page)
{
	size_t	i;

	i = 0;
	while (SPACE_CHAR(page->space)[i])
		write(1, SPACE_CHAR(page->space) + i, 1);
	write(1, " : 0x", 5);
	print_hexa((unsigned long)page->mem);
	write(1, "\n", 1);
}

void	print_mem(unsigned long mem, int j)
{
	write(1, "0x", 2);
	print_hexa(mem);
	write(1, " - 0x", 5);
	print_hexa(mem + j);
	write(1, " : ", 3);
	print_nbr(j);
	j > 1 ? write(1, " octets\n", 8) : write(1, " octet\n", 7);
}

void	show_alloc_mem(void)
{
	t_page	*page;
	size_t	i;
	size_t	j;

	page = g_page;
	print_mem(10, 100);
	while (page)
	{
		print_space(page);
		if (page->space <= SMALL && (i = -1))
			while (++i < page->space)
			{
				while (i < page->space && !(page->empty[i] & START))
					++i;
				j = 0;
				while (i + j < page->space && page->empty[i + j] & FILLED)
					++j;
				if (j)
					print_mem((unsigned long)(page->mem + i), j);
			}
		else
			print_mem((unsigned long)page->mem, page->space);
		page = page->next;
	}
}
