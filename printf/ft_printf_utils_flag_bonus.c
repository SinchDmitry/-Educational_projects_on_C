/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_flag_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:22:04 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 18:10:30 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

t_flag			*ft_null(t_flag *f);
static t_flag	*ft_width(t_flag *f, const char *str, int *i);
static t_flag	*ft_dot(t_flag *f, const char *str, int *i);
static t_flag	*ft_flag(t_flag *f, int a);
t_flag			*flaginit(t_flag *f, const char *str, int *i);

t_flag	*ft_null(t_flag *f)
{
	t_flag	*new;

	new = f;
	if (!f)
	{
		new = malloc(sizeof(t_flag));
		if (!new)
			return (NULL);
	}
	new->fnull = 0;
	new->fspace = 0;
	new->fdiez = 0;
	new->fminus = 0;
	new->fplus = 0;
	new->fdot = 0;
	new->vdot = 0;
	new->fwidth = 0;
	new->vwidth = 0;
	return (new);
}

t_flag	*flaginit(t_flag *f, const char *str, int *i)
{
	int	fl;

	while (++(*i))
	{
		fl = find_chr(1, str[(*i)]);
		if (find_chr(0, str[(*i)]) != -1)
			return (f);
		else if (fl != -1)
			f = ft_flag(f, fl);
		else if (str[(*i)] >= 49 && str[(*i)] <= 57)
		{
			f = ft_width(f, str, i);
			if (str[(*i)] == '.')
				f = ft_dot(f, str, i);
		}
		else if (str[(*i)] == '.')
			f = ft_dot(f, str, i);
		else
		{
			ft_null(f);
			return (f);
		}	
	}
	return (f);
}

static t_flag	*ft_flag(t_flag *f, int a)
{
	if (a == 0 && f->fdot != 1 && f->fwidth != 1)
	{
		f->fminus = 1;
		f->fnull = 0;
	}
	else if (a == 1 && f->fdot != 1 && f->fwidth != 1)
	{
		f->fplus = 1;
		f->fspace = 0;
	}
	else if (a == 2 && f->fplus != 1 && f->fdot != 1 && f->fwidth != 1)
		f->fspace = 1;
	else if (a == 3 && f->fminus != 1 && f->fdot != 1 && f->fwidth != 1)
		f->fnull = 1;
	else if (a == 4)
		f->fdiez = 1;
	return (f);
}

static t_flag	*ft_dot(t_flag *f, const char *str, int *i)
{
	int		start;
	char	*tmp;

	(*i)++;
	start = (*i);
	while ((str[(*i)] >= 48) && (str[(*i)] <= 57))
		(*i)++;
	tmp = ft_substr(str, start, (*i) - start);
	f->fdot = 1;
	f->fnull = 0;
	f->vdot = ft_atoi(tmp);
	free(tmp);
	(*i)--;
	return (f);
}

static t_flag	*ft_width(t_flag *f, const char *str, int *i)
{
	int			start;
	char		*tmp;

	start = (*i);
	while ((str[(*i)] >= 48) && (str[(*i)] <= 57))
		(*i)++;
	tmp = ft_substr(str, start, (*i) - start);
	f->fwidth = 1;
	f->vwidth = ft_atoi(tmp);
	if ((f->vwidth > 2147483638) || (f->vwidth < -2147483638))
		f->vwidth = -1;
	free(tmp);
	(*i)--;
	return (f);
}
