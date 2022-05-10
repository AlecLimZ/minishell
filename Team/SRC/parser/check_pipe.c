/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:42:59 by yang              #+#    #+#             */
/*   Updated: 2022/05/10 13:50:03 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

/* check pipe: check if user input valid syntax for '|'
** Invalid syntax:
** i. '|' located at args[0] or args[last]
** ii. 2 consecutive '|' with no commands
**
** Notes: 
** i. it can be no space in between pipe, echo||echo is valid
** ii. becareful on quotation
*/

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
		while (++j < (int)ft_strlen(check[i]))
		{
			if (check[i][j] == '|')
			{
				if ((j < (int)ft_strlen(check[i]) - 1 && check[i][j + 1] == '|')
					|| (i < len - 1 && check[i + 1][0] == '|') || (i == 0 && j == 0)
					|| (i == len - 1 && j == (int)ft_strlen(check[len  - 1]) - 1))
					return (free_double_ptr(check, true));
			}
			else if (is_quote(check[i][j]))
				j = in_quote(check[i], j);
		}
	}
	return (0);
}
