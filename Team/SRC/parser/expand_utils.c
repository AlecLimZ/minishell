/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:22:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/17 14:20:14 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if env name is valid
** i. start with alpha or '_'
** ii. only consist of alpha, digit or '_'
*/

int	need_expansion(char *str)
{
	int		i;
	int		quote;
	int		quote_open;

	i = -1;
	quote = 0;
	quote_open = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (is_env(str[i + 1]) || str[i + 1] == '?'))
			return (i);
		else if (str[i] == '\'' && quote_open == -1)
			quote = in_quote(str, i);
		else if (str[i] == '"')
		{
			quote_open *= -1;
		}
		if (quote > i)
			i = quote;
	}
	return (-1);
}

static int	env_double_quote(char *str, int i, int *quote_open)
{
	int	quote;
	int	check;

	if (str[i] == '"')
	{
		if (*quote_open == false)
		{
			quote = in_quote(str, i);
			check = i;
			while (++check < quote)
			{
				if (str[check] == '$')
				{
					*quote_open = true;
					return (check);
				}
			}
		}
		else
			*quote_open = false;
	}
	return (0);
}

int	get_env_pos(char *str, int pos)
{
	int			i;
	int			check;
	int			quote;
	static int	quote_open;

	i = pos - 1;
	quote = 0;
	while (str[++i])
	{
		if (i == 0)
			quote_open = false;
		if (str[i] == '$' && str[i + 1]
			&& (is_env(str[i + 1]) || str[i + 1] == '?'))
			return (i);
		else if (str[i] == '\'' && quote_open == false)
			quote = in_quote(str, i);
		check = env_double_quote(str, i, &quote_open);
		if (check)
			return (check);
		if (quote > i)
			i = quote;
	}
	return (-1);
}

int	get_file_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && !is_operator(str[i + len]))
		len++;
	return (len);
}

int	get_redirection_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (GREATGREAT);
	else if (!ft_strncmp(str, "<<", 2))
		return (LESSLESS);
	else if (!ft_strncmp(str, ">", 1))
		return (GREAT);
	else if (!ft_strncmp(str, "<", 1))
		return (LESS);
	return (-1);
}
