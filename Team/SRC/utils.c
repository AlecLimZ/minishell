/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:55:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/22 21:16:21 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		free(s);
	free(s);
}

int	ft_tablen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
