/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:18:08 by cbernot           #+#    #+#             */
/*   Updated: 2023/01/03 09:57:16 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minitalk.h"

int	ft_pow(int nb, int power)
{
	int	res;

	res = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	else
		res *= ft_pow(nb, power - 1);
	return (res);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	c = 0;
	static int	i = 0;
	int			client_pid;

	client_pid = info->si_pid;
	if (signal == SIGUSR2)
		c = c | ft_pow(2, i);
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			if (kill(client_pid, SIGUSR2) != 0);
				exit(EXIT_FAILURE);
			ft_putchar_fd('\n', 1);
		}
		ft_putchar_fd(c, 1);
		kill(client_pid, SIGUSR1);
		i = 0;
		c = 0;
	}
}

int	main()
{	
	struct sigaction	s_act;
	
	ft_putstr_fd("[SERVER]: PID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);

	s_act.sa_sigaction = &signal_handler;
	s_act.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);

	while (1)
		pause();
	return (0);
}
