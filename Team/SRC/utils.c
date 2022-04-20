/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:04:18 by yang              #+#    #+#             */
/*   Updated: 2022/04/18 09:20:41 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

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

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_space(char c)
{
	return (c == '\n' || c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<');
}

int	is_env(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
