/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:42:59 by yang              #+#    #+#             */
/*   Updated: 2022/04/22 14:43:22 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

int	check_pipe_2(char **check, int i, int j)
{
	if (check[0][0] == '|' || check[i][j] == '|')
		return (-1);
	return (0);
}

int	check_pipe(char *str)
{
	char	**check;
	int		i;
	int		j;
	int		len;

	len = count(ft_strtrim(str, " "), ' ');
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
					return (-1);
			}
			else if (is_quote(check[i][j]))
				j = in_quote(check[i], j);
		}
	}
	return (check_pipe_2(check, --i, --j));
}