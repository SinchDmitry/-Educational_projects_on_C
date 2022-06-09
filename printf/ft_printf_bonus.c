/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:34:33 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 18:09:49 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	numer_type(int a, va_list param, char q, t_flag *f);
int			flag_type(int a, va_list param, char c, t_flag *f);
static int	gnrl(const char *str, va_list param);
int			ft_printf(const char *str, ...);
int			find_chr(int f, int c);

int	flag_type(int a, va_list param, char c, t_flag *f)
{
	char	q;
	int		i;

	i = 0;
	q = ' ';
	if (a > 2 && a < 8)
		i = numer_type(a, param, q, f);
	if (a == 0)
		i = rd_ch(f, va_arg(param, int));
	else if (a == 1)
		i = rd_str(f, va_arg(param, void *));
	else if (a == 2)
		i += (rd_hex(f, va_arg(param, unsigned long int), 2));
	else if (a == 8)
		i = ft_putchar(c);
	return (i);
}

static int	numer_type(int a, va_list param, char q, t_flag *f)
{
	int	i;

	i = 0;
	if (f->fnull)
		q = '0';
	if (a != 5)
	{
		if (a == 3 || a == 4)
			i = rd_int(f, va_arg(param, int), q, 1);
		else if (a == 6)
			i = rd_hex(f, va_arg(param, unsigned int), 1);
		else if (a == 7)
			i = rd_hex(f, va_arg(param, unsigned int), 0);
	}
	else
		i = rd_int(f, va_arg(param, unsigned int), q, 0);
	return (i);
}

int	find_chr(int f, int c)
{
	int			i;
	const char	*flags = "-+ 0#";
	const char	*spec = "cspdiuxX%";
	const char	*s;

	i = -1;
	s = flags;
	if (!f)
		s = spec;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	return (-1);
}

static int	gnrl(const char *str, va_list param)
{
	int			counter;
	int			i;
	t_flag		*flags;

	flags = NULL;
	counter = 0;
	i = -1;
	while (str[++i])
	{
		flags = ft_null(flags);
		if (str[i] == '%' && str[i + 1])
		{
			flags = flaginit(flags, str, &i);
			if (flags->vwidth == -1)
				return (-1);
			counter += flag_type(find_chr(0, str[i]), param, str[i], flags);
		}
		else
			counter += ft_putchar(str[i]);
	}
	free (flags);
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
