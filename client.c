/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:18:06 by cbernot           #+#    #+#             */
/*   Updated: 2023/01/03 10:16:21 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minitalk.h"

// SIGUSR1 = 0
// SIGUSR2 = 1
void	send_char(int pid, int c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((1&(c>>i)) == 0)
		{	
			if (kill(pid, SIGUSR1) != 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
				exit(EXIT_FAILURE);
		}
		usleep(100);
		i++;
	}
}

void	send_message(int pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		send_char(pid, msg[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	count_received_char(int signal, siginfo_t *info, void *context)
{
	static int	received = 0;

	if (signal == SIGUSR1)
	{
		ft_putendl_fd("Confirmation received.", 1);
		received++;
	}
	else if (signal == SIGUSR2)
	{
		ft_putnbr_fd(received, 1);
		ft_putendl_fd(" characters received.", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_act;
	
	if (argc != 3)
	{
		ft_putendl_fd("USAGE: ./client [server_pid] [message]", 1);
		exit(EXIT_FAILURE);
	}

	s_act.sa_sigaction = &count_received_char;
	s_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	//signal(SIGUSR1, count_received_char);
	//signal(SIGUSR2, count_received_char);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putendl_fd(" characters sent.", 1);
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}