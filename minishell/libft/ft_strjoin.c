/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:18 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/07 16:39:25 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*tmp;
	long	i;
	long	j;

	j = -1;
	i = ft_strlen(s2) + 1;
	if (s1)
		i = (ft_strlen(s1) + ft_strlen(s2) + 1);
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		error_end(3);
	i = -1;
	if (s1)
		while (s1[++i])
			tmp[i] = s1[i];
	else
		i++;
	while (s2[++j])
		tmp[j + i] = s2[j];
	tmp[j + i] = '\0';
	if (s1)
		free (s1);
	return (tmp);
}

char	*ft_stdstrjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	index = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, size + 1);
	return (str);
}
