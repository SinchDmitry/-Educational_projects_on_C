/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:37:19 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/22 21:19:31 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	vsig(int sig, siginfo_t *send, void *oldact)
{
	(void) sig;
	(void) send;
	(void) oldact;
}

static void	postman(int c, int pid, int f)
{
	int					j;
	int					num;
	struct sigaction	send;

	send.sa_flags = SA_SIGINFO;
	send.sa_sigaction = vsig;
	sigaction(SIGUSR1, &send, NULL);
	j = -1;
	num = 32;
	if (!f)
		num = 8;
	while ((++j) < num)
	{
		if (c & (1 << j))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		usleep(27);
	}	
}

int	ft_atoi(const char *str)
{
	int		i;
	int		a;
	long	res;

	i = 0;
	a = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			a = -a;
	if (str[i] >= 48 && str[i] <= 57)
		while (str[i] >= 48 && str[i] <= 57)
			res = res * 10 - (str[i++] - '0');
	return (a * (int)res);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*str;
	int		nsym;
	int		pid;

	if (argc != 3)
	{
		ft_printf("Wrong number of arguments");
		return (1);
	}
	i = -1;
	str = argv[2];
	pid = ft_atoi(argv[1]);
	nsym = ft_strlen(str);
	postman(nsym, pid, 1);
	while (str[++i])
		postman(str[i], pid, 0);
	postman(str[i], pid, 0);
}
