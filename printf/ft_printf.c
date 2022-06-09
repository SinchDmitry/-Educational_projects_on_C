/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:34:33 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/09 16:54:00 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type(int a, va_list param, char c)
{
	int	i;

	i = 0;
	if (a == 0)
		i = rd_ch(va_arg(param, int));
	else if (a == 1)
		i = rd_str(va_arg(param, void *));
	else if (a == 2)
	{
		write (1, "0x", 2);
		i = (rd_hex(va_arg(param, unsigned long int), 1) + 2);
	}
	else if (a == 3 || a == 4)
		i = rd_int(va_arg(param, int), 1);
	else if (a == 5)
		i = rd_int(va_arg(param, unsigned int), 0);
	else if (a == 6)
		i = rd_hex(va_arg(param, unsigned int), 1);
	else if (a == 7)
		i = rd_hex(va_arg(param, unsigned int), 0);
	else
		i = ft_putchar(c);
	return (i);
}

int	find_chr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

int	gnrl(const char *str, va_list param)
{
	int		counter;
	char	*find;
	int		i;

	counter = 0;
	i = -1;
	find = "cspdiuxX%";
	while (str[++i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			counter += type(find_chr(find, str[i]), param, str[i]);
		}
		else
			counter += ft_putchar(str[i]);
	}
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	va_list		param;
	int			counter;

	va_start (param, str);
	counter = gnrl(str, param);
	va_end (param);
	return (counter);
}
