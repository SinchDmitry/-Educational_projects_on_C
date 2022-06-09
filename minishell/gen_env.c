/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:49:37 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/09 19:51:20 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*==DICTIONARY CREATOR==*/
static t_env	*ft_new_list(char *data)
{
	char	**split;
	t_env	*list;

	if (!data)
		return (NULL);
	split = NULL;
	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->next = NULL;
	if (data)
		split = ft_split(data, '=');
	if (!split)
		return (NULL);
	list->key = split[0];
	list->value = split[1];
	free(split);
	return (list);
}

/*==CONVERT **char env TO DICTIONARY ENV==*/
t_env	*ft_env_to_list(char **env)
{
	t_env	*env_list;
	t_env	*res;

	env_list = ft_new_list(*env);
	if (!env_list)
		return (NULL);
	res = env_list;
	while (env)
	{
		env_list->next = ft_new_list(*env);
		if (!env_list->next)
			return (res);
		env_list = env_list->next;
		env++;
	}
	return (res);
}

char	**ft_new_env(char **env)
{
	int		size;
	int		index;
	char	**new_env;

	index = 0;
	size = 0;
	while (env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * size + 1);
	new_env[index++] = ft_strdup("?=0");
	while (index < size - 1)
	{
		new_env[index] = ft_strdup(env[index]);
		index++;
	}
	new_env[index] = NULL;
	return (new_env);
}

char	**ft_free_env(char **env)
{
	char	**temp;
	void	*str;

	temp = env;
	while (*env)
	{
		str = (void *)*env;
		env++;
		free(str);
	}
	free(temp);
	return (NULL);
}
