/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:18:06 by cbernot           #+#    #+#             */
/*   Updated: 2023/01/12 16:02:03 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

// SIGUSR1 = 0
// SIGUSR2 = 1
// TODO boucle de temps plus petite pour minimiser le decqlqge possible lie 
// a l imprecision de usleep
static void	send_char(int pid, int c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((1 & (c >> i)) == 0)
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

static void	send_message(int pid, char *msg)
{
	unsigned int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		send_char(pid, msg[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{	
	if (argc != 3)
	{
		ft_putendl_fd("USAGE: ./client [server_pid] [message]", 1);
		exit(EXIT_FAILURE);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
