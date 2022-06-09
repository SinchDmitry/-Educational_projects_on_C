/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:37:22 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/23 20:36:43 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	str_construct(int f, int sig, char *str)
{
	static int	i;
	static int	j;
	static int	c;

	if (sig == SIGUSR1)
		c = (c | (1 << i));
	i++;
	if (i == 8)
	{
		str[j++] = c;
		i = 0;
		c = 0;
		if (!str[j - 1])
		{
			ft_printf("%s\n", str);
			f = 0;
			j = 0;
			free(str);
		}
	}
	return (f);
}

static int	len_construct(int f, int sig)
{
	static int	i;
	static int	c;

	if (sig == SIGUSR1)
		c = (c | (1 << i));
	i++;
	if (i == 32)
	{
		f = c;
		i = 0;
		c = 0;
	}
	return (f);
}

void	decoding(int sig, siginfo_t *rec, void *oldact)
{
	static int		f;
	static char		*str;

	(void) oldact;
	if (!f)
		f = len_construct(f, sig);
	if (f < 0)
		f = str_construct(f, sig, str);
	if (f > 0)
	{
		str = malloc(sizeof(char) * (f + 1));
		if (!str)
			return ;
		f = -1;
	}	
	usleep(27);
	kill (rec->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	rec;

	pid = getpid();
	ft_printf("PID of this server : %d\n", pid);
	rec.sa_flags = SA_SIGINFO;
	rec.sa_sigaction = decoding;
	sigaction(SIGUSR1, &rec, NULL);
	sigaction(SIGUSR2, &rec, NULL);
	while (1)
		pause ();
}
