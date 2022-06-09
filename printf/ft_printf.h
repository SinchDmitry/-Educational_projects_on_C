/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:35:47 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/08 22:56:36 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);

int		type(int a, va_list param, char c);

int		find_chr(const char *s, int c);

int		rd_ch(char c);

int		rd_str(char *c);

int		rd_ptr(unsigned long int a);

int		rd_int(int a, int f);

int		rd_hex(unsigned long int a, int f);

int		ft_putchar(char c);

void	ft_putnbr(long int n, int *i);

int		gnrl(const char *str, va_list param);

#endif