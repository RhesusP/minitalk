/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:18:08 by cbernot           #+#    #+#             */
/*   Updated: 2023/01/13 00:18:53 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

/**
 * @brief Add the character 'c' at the end of the string 'str' (it creates a new
 * string and free the parameter).
 * 
 * @param str Base string
 * @param c Char to add.
 * @return char* str with c as last char. 
 */
static char	*add_char_to_str(char *str, char c)
{
	char			*res;
	size_t			len;
	unsigned int	i;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	if (len > 0)
		free (str);
	return (res);
}

/**
 * @brief Signal handler for SIGUSR1 and SIGUSR2 used to receive and recreate
 * a char byte by byte.
 * 
 * @param signal Received signal id.
 */
static void	signal_handler(int signal)
{
	static int	c = 0;
	static int	i = 0;
	static char	*str = "";

	if (signal == SIGUSR2)
		c = c | 1 << i;
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			ft_putstr_fd(str, 1);
			if (ft_strlen(str) > 0)
				free (str);
			str = "";
		}
		str = add_char_to_str(str, c);
		i = 0;
		c = 0;
	}
}

int	main(void)
{	
	ft_putstr_fd("[SERVER]: PID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	while (1)
		pause();
	return (0);
}
