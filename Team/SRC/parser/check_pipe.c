/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:42:59 by yang              #+#    #+#             */
/*   Updated: 2022/05/05 12:14:13 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check pipe: check if user input valid syntax for '|'
** Invalid syntax:
** i. '|' located at args[0] or args[last]
** ii. more than 2 consecutive '|'
**
** Notes: 
** i. echo || echo is valid
** ii. it can be no space in between pipe, echo||echo is valid
** iii. becareful on quotation
*/

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
				if ((j < (int)ft_strlen(check[i]) - 2 && check[i][j + 2] == '|')
					|| (i < len - 1 && check[i + 1][0] == '|'))
					return (free_double_ptr(check, true));
			}
			else if (is_quote(check[i][j]))
				j = in_quote(check[i], j);
		}
	}
	return (check_pipe_2(check, --i, --j));
}
