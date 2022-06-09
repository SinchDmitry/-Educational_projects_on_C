/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:15:58 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 05:36:08 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_open_redir_in(int *in, int *her, int mode, t_arg *redir)
{
	int	heredoc;
	int	infile;

	infile = 0;
	if (redir->type == L_REDIR && mode == 1)
	{
		heredoc = 0;
		if (infile != -1)
			close(infile);
		infile = open(redir->path, O_RDONLY);
		if (infile == -1)
		{
			ft_putstr_fd("file not found\n", 2);
			return (1);
		}
	}
	if (redir->type == HEREDOC && mode == 1)
		heredoc = 1;
	*her = heredoc;
	*in = infile;
	return (0);
}

static int	ft_open_redir_out(int *out, int mode, t_arg *redir)
{
	int	outfile;

	outfile = 0;
	if (redir->type == R_REDIR && mode == 0)
	{
		if (outfile != -1)
			close(outfile);
		outfile = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile == -1)
			return (0);
	}
	if (redir->type == DR_REDIR && mode == 0)
	{
		if (outfile != -1)
			close(outfile);
		outfile = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile == -1)
			return (0);
	}
	*out = outfile;
	return (0);
}

static int	ft_apply_redirect(int infile, int outfile, int heredoc, int mode)
{
	char	buf;
	int		byte;

	byte = 1;
	if (infile != -1 && !heredoc && mode == 1)
	{
		while (byte != 0)
		{
			byte = read(infile, &buf, 1);
			if (byte == -1)
				return (0);
			if (byte)
				write(1, &buf, 1);
		}
	}
	if (outfile != -1 && mode == 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	if (infile != -1)
		close(infile);
	byte = 1;
	return (0);
}

int	ft_redir(t_arg *redir, int mode)
{
	int		infile;
	int		outfile;
	int		heredoc;
	int		file_status;

	heredoc = 0;
	infile = -1;
	outfile = -1;
	file_status = 0;
	while (redir)
	{
		ft_open_redir_out(&outfile, mode, redir);
		file_status = ft_open_redir_in(&infile, &heredoc, mode, redir);
		redir = redir->next;
	}
	ft_apply_redirect(infile, outfile, heredoc, mode);
	if (heredoc)
		return (HEREDOC);
	return (file_status);
}

// char	*ft_heredoc_wheel(t_arg *redir, t_cmd *cmd)
// {
// 	char	*str;
// 	char	*final;

// 	final = NULL;
// 	if (redir->type == HEREDOC)
// 	{
// 		str = readline("> ");
// 		final = ft_strdup("");
// 		if (!final)
// 			error_end(3);
// 		ft_pfree(&cmd, final);
// 		while (ft_strcmp(str, redir->path))
// 		{
// 			final = ft_stdstrjoin(final, str);
// 			if (!final)
// 				error_end(3);
// 			ft_pfree(&cmd, final);
// 			final = ft_stdstrjoin(final, "\n");
// 			if (!final)
// 				error_end(3);
// 			ft_pfree(&cmd, final);
// 			free(str);
// 			str = readline("> ");
// 		}
// 		free(str);
// 	}
// 	return (final);
// }

char	*ft_heredoc(t_arg *redir, t_cmd *cmd)
{
	char	*final;
	char	*str;

	final = NULL;
	str = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC)
			final = ft_heredoc_wheel(redir, cmd, final, str);
		redir = redir->next;
	}
	return (final);
}
