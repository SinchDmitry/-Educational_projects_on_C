/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:59:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 01:18:19 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_free	*ft_new_free_list(void *pointer)
{
	t_free	*list;

	list = (t_free *)malloc(sizeof(t_free));
	if (!list)
		error_end(3);
	list->next = NULL;
	list->pointer = pointer;
	return (list);
}

static void	ft_add_free_list(t_free **head, void *pointer)
{
	t_free	*list;

	if (!*head)
	{
		*head = ft_new_free_list(pointer);
		if (!*head)
			return ;
		return ;
	}
	list = *head;
	while (list->next)
	{
		list = list->next;
	}
	list->next = ft_new_free_list(pointer);
}

void	ft_pfree(t_cmd **command, char *pointer)
{
	t_cmd	*cmd;

	cmd = *command;
	ft_add_free_list(&cmd->free, (void *)pointer);
}

void	ft_ppfree(t_cmd **command, char **pointer)
{
	t_cmd	*cmd;

	cmd = *command;
	ft_add_free_list(&cmd->free, (void *)pointer);
	while (*pointer)
		ft_pfree(&cmd, *(pointer++));
}

void	ft_free_all(t_cmd *cmd)
{
	t_free	*temp;

	while (cmd->free)
	{
		free(cmd->free->pointer);
		temp = cmd->free;
		cmd->free = cmd->free->next;
		free(temp);
	}
}
