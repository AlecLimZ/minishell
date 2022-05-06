/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:22:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/04 15:32:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!is_env(str[i]))
			return (0);
	}
	return (1);
}

int	get_env_pos(char *str, int pos)
{
	int	i;
	int	quote;

	i = pos - 1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			return (i);
		else if (str[i] == '\'')
			quote = in_quote(str, i);
		if (quote > i)
			i = quote;
	}
	return (-1);
}

char	*get_prefix(char *str, int i)
{
	if (i > 0)
		return (ft_strndup(str, i));
	return (NULL);
}

char	*get_postfix(char *str, int *i)
{
	int		postfix_pos;
	int		j;

	postfix_pos = 0;
	j = *i;
	while (str[++j])
	{
		if (!is_env(str[j]))
		{
			postfix_pos = j;
			break ;
		}
	}
	if (postfix_pos != 0)
		return (ft_strndup(str + j, ft_strlen(str) - j));
	return (NULL);
}