/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:36:49 by cbernot           #+#    #+#             */
/*   Updated: 2022/12/17 14:01:28 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((unsigned char)s[i] != (unsigned char)'\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&(s[i]));
		i++;
	}
	if ((unsigned char)c == (unsigned char)'\0')
		return ((char *)&(s[i]));
	return ((char *)(0));
}
