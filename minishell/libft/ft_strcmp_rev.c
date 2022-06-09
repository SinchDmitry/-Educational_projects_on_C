/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:03:42 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/06 18:09:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strcmp_rev(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (j > -1)
	{
		if (i == -1)
			return (-1);
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		i--;
		j--;
	}
	return (0);
}
