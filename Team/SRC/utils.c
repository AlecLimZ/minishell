/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:04:18 by yang              #+#    #+#             */
/*   Updated: 2022/03/29 17:49:30 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	in_quote(char *str, int i)
{
	char	quote;
	int		opened;

	opened = 0;
	if ((str[i] == '\'' || str[i] == '"') && opened == 0)
	{
		quote = str[i];
		opened = 1;
	}
	while (str[++i])
	{
		if (str[i] == quote)
		{
			opened = 0;
			return (i);
		}
	}
	if (opened == 1)
		return (-1);
	return (i);
}

int	is_space(char c)
{
	return (c == '\n' || c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<');
}
