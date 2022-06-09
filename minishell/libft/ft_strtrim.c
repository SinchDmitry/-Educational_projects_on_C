/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:50 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 04:23:35 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		a;
	int		tmp;
	char	*res;

	i = 0;
	a = -1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	tmp = i - 1;
	while (s1[i])
		i++;
	while (i >= 0 && ft_strchr(set, s1[i]) && i > tmp)
		i--;
	res = malloc(sizeof(char) * ((i - tmp) + 1));
	if (!res)
		return (NULL);
	while (tmp <= i)
		res[++a] = s1[++tmp];
	res[a] = '\0';
	free(s1);
	return (res);
}

char	*ft_isspace_strtrim(char *s1)
{
	int		i;
	int		a;
	int		tmp;
	char	*res;

	i = 0;
	a = -1;
	while (space(s1[i]))
		i++;
	tmp = i - 1;
	while (s1[i])
		i++;
	while (i >= 0 && space(s1[i]) && i > tmp)
		i--;
	res = malloc(sizeof(char) * ((i - tmp) + 1));
	if (!res)
		return (NULL);
	while (tmp <= i)
		res[++a] = s1[++tmp];
	res[a] = '\0';
	free(s1);
	return (res);
}
