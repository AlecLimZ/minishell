/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:35:26 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/25 13:41:20 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char(void)
{
	char	buf[4];
	int		nbr;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buf, 4);
	nbr = *(int *)buf;
	if (nbr < 0)
		nbr *= (-1);
	return ('a' + nbr % 26);
}

char	*ft_create_file(void)
{
	char	*filename;
	int		i;

	i = -1;
	filename = malloc(sizeof(char) * 11);
	filename[10] = '\0';
	while (++1 < 10)
		filename[i] = (char)ft_char();
	return (filename);
}
