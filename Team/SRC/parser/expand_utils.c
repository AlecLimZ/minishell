/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:22:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/11 00:13:30 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

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

int	get_env_pos(char *str, int pos)
{
	int		i;
	int		check;
	int		quote;
	static	int quote_open;

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
		else if (str[i] == '"')
		{
			if (quote_open == false)
			{
				quote = in_quote(str, i);
				check = i;
				while (++check < quote)
				{
					if (str[check] == '$')
					{
						quote_open = true;
						return (check);
					}
				}
			}
			else
				quote_open = false;
		}
		if (quote > i)
			i = quote;
	}
	return (-1);
}
