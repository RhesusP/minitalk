/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:18:06 by cbernot           #+#    #+#             */
/*   Updated: 2023/01/18 08:31:48 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

/**
 * @brief Send a char byte by byte using SIGUSR1 and SIGUSR2.
 * We use a loop with a shorter duration to decrease the bit shifting
 * due to usleep imprecision.
 * 
 * @param pid PID of the server.
 * @param c The char to send.
 */
static void	send_char(int pid, int c)
{
	int	i;
	int	j;

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
		j = 0;
		while (j < 10)
		{
			usleep(10);
			j++;
		}
		i++;
	}
}

/**
 * @brief Send a string char by char thanks to signals.
 * 
 * @param pid PID of the server. 
 * @param msg String to send.
 */
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
