/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:54:49 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/10 13:34:59 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	rd_ch( char c)
{
	ft_putchar(c);
	return (1);
}

int	rd_str(char *c)
{
	int	i;

	i = -1;
	if (c)
		while (c[++i])
			ft_putchar(c[i]);
	else
	{
		write(1, "(null)", 6);
		i = 6;
	}
	return (i);
}

int	rd_int(int a, int f)
{
	int				i;
	unsigned int	b;

	i = 0;
	b = (unsigned int)a;
	if (!f)
		ft_putnbr(b, &i);
	else
		ft_putnbr(a, &i);
	return (i);
}

int	rd_hex(unsigned long int a, int f)
{
	char				*base;
	char				word[19];
	unsigned long int	tmp;
	int					i;

	base = "0123456789abcdef";
	if (!f)
		base = "0123456789ABCDEF";
	word[0] = '0';
	i = 0;
	tmp = a;
	if (!a)
		i = 1;
	while (a)
	{
		a = a / 16;
		word[i++] = base[tmp - (a * 16)];
		tmp = a;
	}
	tmp = i;
	while (--i >= 0)
		ft_putchar(word[i]);
	return (tmp);
}
