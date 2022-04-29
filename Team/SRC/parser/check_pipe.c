/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:42:59 by yang              #+#    #+#             */
/*   Updated: 2022/04/29 13:48:53 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_2(char **check, int i, int j)
{
	if (check[0][0] == '|' || check[i][j] == '|')
		return (free_double_ptr(check, true));
	return (free_double_ptr(check, false));
}

int	check_pipe(char *str)
{
	char	**check;
	int		i;
	int		j;
	int		len;

	len = count(str, ' ');
	check = ft_split_str(str, ' ');
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (j < (int)ft_strlen(check[i]) && check[i][++j] != '\0')
		{
			if (check[i][j] == '|')
			{
				if ((j < (int)ft_strlen(check[i]) - 1 && check[i][j + 1] == '|')
					|| (i < len - 1 && check[i + 1][0] == '|'))
					return (free_double_ptr(check, true));
			}
			else if (is_quote(check[i][j]))
				j = in_quote(check[i], j);
		}
	}
	return (check_pipe_2(check, --i, --j));
}
