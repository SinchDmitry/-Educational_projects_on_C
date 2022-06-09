/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:22 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 07:48:05 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>  
# include "libft/libft.h"
# include <termios.h>

# define L_REDIR 1
# define R_REDIR 2
# define HEREDOC 3
# define DR_REDIR 4

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

typedef struct s_free
{
	struct s_free	*next;
	void			*pointer;
}	t_free;

typedef struct s_malloc_c
{
	struct s_malloc_c	*next;
	char				*point;
}	t_malloc_c;

typedef struct s_var
{
	int		red_c;
	int		arg_c;
	int		a;
	int		n;
	int		m;
	int		*temp;
	int		*temp_prev;
	char	q_ch;
}	t_var;

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

typedef struct s_fd
{
	int	i;
	int	error;
}	t_fd;

typedef struct s_arg
{
	struct s_arg	*next;
	int				type;
	char			*path;
	char			*tmp_var;
}	t_arg;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			**argum;
	t_free			*free;
	t_pipe			pipe;
	t_arg			*args;
	t_arg			*redir;
	int				var_or;
	int				and;
	int				sub;
	int				wild;
}	t_cmd;

typedef struct s_data
{
	struct s_data	*next;
	struct s_data	*prev;
	char			sym;
	int				pipe_out_flag;
	int				pipe_in_flag;
	int				parse_error;
	int				red_counter;
	int				red_first;
	int				her_first;
	int				and_first;
	int				red_addr;
	int				or_first;
	int				double_q;
	int				once_q;
	int				redir;
	int				hooks;
	int				args;
	int				wild;
	int				var;
	int				cmd;
	int				and;
	int				or;
	int				rm;
}	t_data;

/* general */
void		error_end(int flag);
int			ft_start(char *str, char ***env);

/* env */
char		**ft_new_env(char **env);
char		**ft_free_env(char **env);

/* pre utils */
int			space(char sym);
int			iscmd(char sym);
void		re_init(t_data *tmp);
t_env		*ft_env_to_list(char **env);
void		add_back_or_new(t_data **lst, t_data *new);

/* pre commands & pre redirect*/
void		or_check(t_data *tmp);
void		red_check(t_data *tmp);
void		and_check(t_data *tmp);
void		cmd_check(t_data *tmp);
void		red_addr_check(t_data *tmp);

/* pre arguments */
void		rm_check(t_data *tmp);
void		arg_check(t_data *tmp);
void		hooks_check(t_data *tmp);
void		quote_check(t_data *tmp, int num_quote);

/* pre parser & pre check*/
t_data		*sym_parse(char *str);
void		pre_check(t_data *tmp);
void		pre_check_first(t_data *tmp);
t_data		*pre_parse_it(char sym, t_data *prev);

/* gen utils */
void		add_back_or_new_cmd(t_cmd **lst, t_cmd *new);
void		add_back_or_new_arg(t_arg **lst, t_arg *new);
t_cmd		*init_func(t_var *cntr, t_data *sym);
void		fd_init(int fd[2][2], int red_fd[2], t_fd **var, t_cmd *head);

/* gen checker & gen parser*/
char		**conv_to_str(t_arg *args);
t_cmd		*cmd_parse(t_cmd *tmp, t_data *sym, char ***env);
int			break_mod(t_data **sym, t_var c, int mod);
void		gen_check(t_data **sym, t_cmd *tmp, t_var *cntr, char **env);
t_arg		*gen_arg_check(t_data **sym, t_cmd *tmp, char **env, int mod);
void		gen_flag_check(t_data **sym, t_cmd *tmp, t_arg *local, char **env);

/* gen wilcard */
void		wildcard_add(t_data **sym, t_cmd *tmp);

/* gen free */
void		kill_env(t_env *env);
void		clear_point(t_malloc_c *malloc_h);
t_malloc_c	*save_point(void *mal_p, int flag);

/* BUILD */
int			ft_exec_com(t_cmd *com, char ***env, int fd[2][2], int red_pipe[2]);

/* build/cd.c */
int			ft_cd(char *path, char ***g_env);

/* build/echo.c */
int			ft_echo(char **av);

/* build/env.c */
int			ft_env(char **env);

/* build/exit.c */
void		ft_exit(int exit);

/* build/export.c */
int			ft_max(char **env);
int			ft_pars(char *str);
int			ft_check_eq(char *str);
int			ft_export(char ***env, char **arg);
int			ft_check_double(char *str, char **arg);
int			ft_unset(char ***env, char **arg, int flag);
char		**ft_exp_utils(char **arg, int *status, int *index, char **new_env);
char		**ft_new_arg(char **arg, char **tmp);

/* build/utils.c */
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_stdstrjoin(char const *s1, char const *s2);

/* build/pwd.c */
int			ft_pwd(char **env);
int			minishell(t_cmd *command, char ***env, int fd[2][2], int red_fd[2]);

/* signals */
void		ft_sig(int signum);
int			ft_signal(void);
void		rl_replace_line(const char *buffer, int val);

/* build free */
void		ft_free_all(t_cmd *cmd);
void		ft_pfree(t_cmd **command, char *pointer);
void		ft_ppfree(t_cmd **command, char **pointer);

/* build redirect */
int			ft_check_in(t_cmd command);
int			ft_check_out(t_cmd command);
int			ft_redir(t_arg *redir, int mode);
char		*ft_heredoc(t_arg *redir, t_cmd *cmd);
int			ft_redir_in(t_cmd *com, int fd[2][2], int red_pipe[2], char *here);
char		*ft_heredoc_wheel(t_arg *redir, t_cmd *cmd, char *final, char *str);

/* build pipe */
int			ft_close(int fd[2][2]);
int			ft_close_pipe(int fd[2][2], t_cmd command);
int			ft_pipex(int red_pipe[2], int fd[2][2], t_cmd *command);
int			ft_pipe_setting(int fd[2][2], int red_fd[2], t_cmd *command);

/* build path */
char		*ft_find_command(t_cmd *command, char **env);
char		*ft_return_path(char **paths, char *arg, t_cmd *command);
char		*ft_get_env(char **env, char *str);

/* build system */
void		ft_system(t_cmd *command, char **env);
int			ft_system_parent(t_cmd *command, char ***env);

#endif
